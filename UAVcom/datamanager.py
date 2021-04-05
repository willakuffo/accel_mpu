
import os
import pickle
dir = os.path.join(os.getcwd(),'flight_data')
flight_manuevers = []
flight_episodes = []


def get_episodes():
	i = 1
	total_samples = 0
	total_episodes = 0
	print('FLIGHT CATEGORY         |NO. EPISODES','| SAMPLE SIZE\n---------------------------------------------------')
	for roots,dirs,files in os.walk(dir):
		flight_category = roots.split('/')[-1] 
		flight_manuevers.append(flight_category)
		flight_episodes.append(files)
	#print(flight_episodes)
	
	flight_episodes.pop(0) #pop base dir ->flight_data
	flight_manuevers.pop(0) #same

	for flight_category,episodes in zip(flight_manuevers,flight_episodes):
		sample_size = 0
	
		if len(episodes)>0:
			for episode in episodes:
				with open('flight_data/'+flight_category+'/'+episode,'rb') as e:
					sample_size+= len(pickle.load(e))
			total_samples+=sample_size
		total_episodes+=len(episodes)

		print('{:<5}'.format(str(i)),'{:<17} |'.format(flight_category),len(episodes),'          |      ',sample_size)
		i = i+1
	
	print('Current Record:','  total episodes: ',total_episodes,' total_samples: ',total_samples,'\n')
		
	try:
		option = input('select flight category to collect data for [1..14]:')
		samples = input('collect [n] samples:')
		flight_category = flight_manuevers[eval(option)-1]
		os.system('sudo python3.7 serialcom.py '+flight_category+' '+samples)
		#os.system('sudo python3.7 serialcom.py')
	except SyntaxError:
		print('Exit')
get_episodes()
