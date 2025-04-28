import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt 
import os
import tensorflow as tf 

data = pd.read_csv('/home/Dhyan/Documents/AI-Lab/Exp-7/Housing_Price_Data (1).csv')
print(data.head())

x = data.drop(['price'], axis=1)
y = data['price']

from sklearn.preprocessing import LabelEncoder
le = LabelEncoder()
x['furnishingstatus'] = le.fit_transform(x['furnishingstatus'])

binary_columns = ["mainroad", "guestroom", "basement", "hotwaterheating", "airconditioning", "prefarea"]
x[binary_columns] = x[binary_columns].apply(lambda x: x.map({"yes": 1, "no":  0}))
print(x.head())

from sklearn.model_selection import train_test_split

x_train,x_test,y_train,y_test = train_test_split(x,y,test_size=0.2,random_state=42)

x_train,x_valid,y_train,y_valid = train_test_split(x_train, y_train)

from keras import Sequential
from keras.layers import Dense

model = Sequential()
model.add(Dense(128, activation="relu",input_shape=(12,)))
model.add(Dense(64, activation="relu"))
model.add(Dense(78, activation="relu"))
model.add(Dense(32, activation="relu"))
model.add(Dense(1, activation="linear"))

print(model.summary())

model.compile(loss="mean_squared_error", optimizer="adam", metrics=['mae'])
hist = model.fit(x_train, y_train, epochs=100, validation_data=(x_valid,y_valid))

y_predict = model.predict(x_test)
print(y_predict)

from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

mae = mean_absolute_error(y_test,y_predict)
mse = mean_squared_error(y_test, y_predict)
r2 = r2_score(y_test, y_predict)
print("Absolute: ", mae)
print("Squared: ", mse)
print("r2: ", r2)