import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt 
import os
import tensorflow as tf 

data = pd.read_csv('/home/Dhyan/Documents/AI-Lab/Exp-7/Class_heart_attack.csv')
print(data.describe())

x = data.drop(['target'], axis=1)
y = data['target']

from sklearn.model_selection import train_test_split

x_train,x_test,y_train,y_test = train_test_split(x,y,test_size=0.2, random_state=42)

x_train,x_valid,y_train,y_valid = train_test_split(x_train, y_train)

from keras import Sequential
from keras.layers import Dense

model = Sequential()
model.add(Dense(128, activation="sigmoid",input_shape=(13,)))
model.add(Dense(64, activation="sigmoid"))
model.add(Dense(78, activation="sigmoid"))
model.add(Dense(32, activation="sigmoid"))
model.add(Dense(1, activation="sigmoid"))

model.compile(loss="binary_crossentropy", optimizer="adam", metrics=['accuracy'])

hist = model.fit(x_train, y_train, batch_size=32,epochs=75,validation_data=(x_valid,y_valid))

y_predict = model.predict(x_test)

from sklearn.metrics import classification_report

print(classification_report(y_test,y_predict.round()))

