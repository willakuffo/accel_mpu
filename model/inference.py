import tensorflow as tf
import pickle 
import numpy as np
import time
#load model scaler config
scaler_config = None
print()
with open('scaler_config.pickle','rb') as c:
	scaler_config = pickle.load(c)

#init tflite interpreter and allocate tensors
Interpreter = tf.lite.Interpreter(model_path = 'accel_mae_Nadam_model.tflite')
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

st = time.time()
print(infer(scale_input(np.ones([1,31]))))
print('infer time:',time.time()-st)

a = scale_input(np.zeros([1,31]))
print(a,unscale_output(a))
