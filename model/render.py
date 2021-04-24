import numpy as np
import streamlit as st
import pandas as pd
import random
from plotly import graph_objects as go
from collections import deque
import plotly.express as px

class Render:

	def __init__(self):
		self.df = pd.DataFrame({})
		self.df['xtruth'] = [0]
		self.df['ytruth'] = [0]
		self.df['ztruth'] = [0]
		self.df['xpred'] = [0]
		self.df['ypred'] = [0]
		self.df['zpred'] = [0]

		self.xtruth = []
		self.ytruth = []
		self.ztruth = []
		self.xpred = []
		self.ypred = []
		self.zpred = [] 		
		print(self.df)
		self.fig = go.Figure()
		#self.plot_bufferi = deque(maxlen = 100)
		#self.plot_buffero = deque(maxlen = 100)
		#self.fig = go.Figure()
		#pass
	def update_df(self,truth,pred):
		data_in = pd.concat([pd.DataFrame(truth),pd.DataFrame(pred)],axis = 1)
		data_in.columns = ['xtruth','ytruth','ztruth','xpred','ypred','zpred']
		self.df = pd.concat([self.df,data_in])
		

	def make2d_out_vis(self,new_data):
		#self.fig.add_trace(go.Scatter( y=self.df['xtruth'],mode='lines',name='markers'))
		self.fig = px.line(self.df,y = 'xtruth')
		st.write(self.fig)




#R = Render()
#with st.empty():
#	while True:
		#print(random.random())
#		R.make2dvis()
