import streamlit as st
import sys
import os
sys.path.insert(0,os.path.join(os.getcwd().rstrip('/model'),'UAVcom'))
import serialcom
import tensorflow as tf
import pickle 
import numpy as np
import time
import render
pred = []
true = []

#load model scaler config
scaler_config = None

with open('scaler_config_1.pickle','rb') as c:
	scaler_config = pickle.load(c)

#init tflite interpreter and allocate tensors
Interpreter = tf.lite.Interpreter(model_path = 'accel_mae_Nadam_model_1.tflite')
Interpreter.allocate_tensors()

output_details = Interpreter.get_output_details()
input_details = Interpreter.get_input_details()
input_shape = input_details[0]['shape']
#print(output_details, input_details)


def infer(input_data):
	input_data = np.array(input_data,dtype = np.float32)
	Interpreter.set_tensor(input_details[0]['index'],input_data)
	Interpreter.invoke()
	predicted = Interpreter.get_tensor(output_details[0]['index'])
	return predicted

def scale_input(input):
	scaled_features = []
	input_config = scaler_config['input_scaler']
	for feature_max,feature_min,input_feature in zip(input_config['max'],input_config['min'],input[0]):
		scaled = (input_feature - feature_min)/(feature_max-feature_min)
		scaled_features.append(scaled)
				
		#print(feature_max,feature_min,input_feature)
	return np.reshape(np.array(scaled_features),(1,-1))

def unscale_output(output):
	unscaled_features = []
	output_config = scaler_config['output_scaler']
	for feature_max,feature_min,output_feature in zip(output_config['max'],output_config['min'],output[0]):
		unscaled = output_feature*(feature_max-feature_min)+feature_min
		unscaled_features.append(unscaled)
	return np.reshape(np.array(unscaled_features),(1,-1))

start = time.time()
print(infer(scale_input(np.ones([1,31]))))
print('infer time:',time.time()-start)


a = scale_input(np.zeros([1,31]))
print(a,unscale_output(a))

out_features = ['travel_x', 'travel_y', 'travel_z']
in_features =  ['time','dt','accel_ms_x', 'accel_ms_y', 'accel_ms_z', 'accel_ang_x', 'accel_ang_y', 'gyro_deg_x', 'gyro_deg_y', 'gyro_deg_z',
	 'gyro_ang_x', 'gyro_ang_y', 'gyro_ang_z', 'com_pitch', 'com_roll', 'com_yaw', 'IMU_vel_x', 'IMU_vel_y', 'IMU_vel_z', 'IMU_dist_x', 
	 'IMU_dist_y', 'IMU_dist_z', 'chng_velx', 'chng_vely', 'chng_velz', 'chng_distx', 
	 'chng_disty', 'chng_distz', 'chng_axp', 'chng_ayp', 'chng_azp']
S = serialcom.serialstream(baudrate = 115200)
R = render.Render()

print(S.keys)
with st.empty():
	while True:
		try:
			data = S.stream(format=True, format_type={}, keys=S.keys, expected_feature_size=34, record=False)
			if data is not None:
				input_data = np.reshape(np.array(list(dict((k,data[k]) for k in in_features).values())),(1,-1))
				output_data = np.reshape(np.array(list(dict((k,data[k]) for k in out_features).values())),(1,-1))
				predicted = unscale_output(infer(scale_input(input_data)))
				print('true:', output_data,'          predicted:',predicted)
				pred.append(predicted[0])
				true.append(output_data[0])
				#st.write(predicted)
				#R.update_df(output_data,predicted)
				#R.make2d_out_vis(np.array([predicted[0][0],output_data[0][0]]))
		except KeyboardInterrupt:
			print('saving prediction experiment')
			filename = input('filename: ')
			with open(filename+'.pickle','wb') as p:
				pickle.dump([true,pred],p)
				p.close()
			break

