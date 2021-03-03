import serial
import pickle
import os
from datetime import datetime
import numpy as np

class serialstream:
	def __init__(self,port = '/dev/ttyS0',baudrate = 9600):
		self.port = port
		self.baudrate = baudrate
		self.connection = serial.Serial(self.port,baudrate = self.baudrate)
		self.data = None
		self.data_len = None

		self.record_file_base_name = 'UAV_episode'
		self.episode_record = [] #list()
		#while True:
		#	if self.c.in_waiting>0:print(self.c.readline())


	def stream(self,format = False,format_type = None, keys = None,expected_feature_size = None,record = False):
		'''if format <bool>: format data and return type and ensure right number of features are reurned because serial is asynchronous and can lose some.Else return decoded utf-8 data
		   if format type is []: if format is true, return data as  decoded utf-8 with each item's eval. d
		   if format_type is {}: if format is true, return data as decoded utf-8 as dict with keys as keys and values as []. Each itm assigned to key
		   expected_size <int>: effective when format is True. return only on expected feature size because serial might lose some'''
		try: #try to get data
			if self.connection.in_waiting>0: #if data is available
				self.data = self.connection.readline() #read data
				self.data = self.data.decode().split() #separate/split features by single whitespeace
				self.data_len = len(self.data)	#get number of features in this read
				# format
				#allow the option to format without right feature size, Not recommended. if [],feeatures may not be at right indices when because serial may lose some
				#if {}, keys may not be assigned to right features
				if expected_feature_size is None:expected_feature_size = self.data_len 

				if format: #ensure the right number of features is returned
						if type(format_type) is list:
							self.data =  [eval(feature) for feature in self.data]
						elif type(format_type) is dict:
							try:
								self.data = dict(zip(keys,[eval(feature) for feature in self.data]))
							except TypeError:
								raise ValueError('Keys is None, not provided')

				if record: self.episode_record.append(self.data)

				if expected_feature_size == self.data_len: # return only the formatted right sized features
					return self.data		
								
				elif not format: return self.data #return unformatted option	
		#if exception, try to handle
		except serial.serialutil.SerialException:
			print('serial_exc')
			pass

		except OSError:
			print('OSerror')
			try:
				#self.connection.flush()
				self.connection = serial.Serial(self.port,baudrate = self.baudrate)
				print('reinit')
			except:
				self.connection.flush()
				self.connection = serial.Serial(self.port,baudrate = self.baudrate)
				print('reinit2')

	def save_episode(self):
		'''save recorded data -> state variables of UAV flight'''
		with open(self.record_file_base_name+str(datetime.today())+'.pickle','wb') as record:
			pickle.dump(self.episode_record,record)
			record.close()	
	

if __name__ =='__main__':
	S = serialstream(baudrate = 115200)
	expected_feature_size = 34
	keys = list(np.zeros([1,expected_feature_size])[0]) #init keys
	keys[0] = 'time'
	keys[1] = 'dt'
	keys[2] = 'travel_x'
	keys[3] = 'travel_y'
	keys[4] = 'travel_z'
	keys[5] = 'accel_ms_x'
	keys[6] = 'accel_ms_y'
	keys[7] = 'accel_ms_z'
	keys[8] = 'accel_ang_x'
	keys[9] = 'accel_ang_y'
	keys[10] = 'gyro_deg_x'
	keys[11] = 'gyro_deg_y'
	keys[12] = 'gyro_deg_z'
	keys[13] = 'gyro_ang_x'
	keys[14] = 'gyro_ang_y'
	keys[15] = 'gyro_ang_z'
	keys[16] = 'com_pitch'
	keys[17] = 'com_roll'
	keys[18] = 'com_yaw'
	keys[19] = 'IMU_vel_x'
	keys[20] = 'IMU_vel_y'
	keys[21] = 'IMU_vel_z'
	keys[22] = 'IMU_dist_x'
	keys[23] = 'IMU_dist_y'
	keys[24] = 'IMU_dist_z'
	keys[25] = 'chng_velx'
	keys[26] = 'chng_vely'
	keys[27] = 'chng_velz'
	keys[28] = 'chng_distx'
	keys[29] = 'chng_disty'
	keys[30] = 'chng_distz'
	keys[31] = 'chng_axp'
	keys[32] = 'chng_ayp'
	keys[33] = 'chng_azp'

	while True:
		try:
			data = S.stream(format = True,format_type = {},keys = keys,expected_feature_size = expected_feature_size,record = True)
			if data is not None:
				print(data,len(data))
		except KeyboardInterrupt:
			print('Saving flight episode...')
			save = input('Save this flight episode [y/n]?')
			if save.lower() == 'y':
				S.save_episode()
				print('Done!')
			else:
				print('discarded episode.')
			break
    			
