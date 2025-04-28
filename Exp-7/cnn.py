import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt 
import os
import tensorflow as tf 

print("Number of image:", len(os.listdir('/home/Dhyan/Documents/AI-Lab/Exp-7/Plant Disease/Train/Corn_(maize)___Common_rust_')))
from tensorflow.keras.preprocessing.image import ImageDataGenerator

train_gen=ImageDataGenerator(
    rescale=1.0/255,
    rotation_range=20
)
test_gen=ImageDataGenerator(
    rescale=1.0/255
)

train_data=train_gen.flow_from_directory('/home/Dhyan/Documents/AI-Lab/Exp-7/Plant Disease/Train', target_size=(126,126), class_mode="categorical")
test_data=test_gen.flow_from_directory('/home/Dhyan/Documents/AI-Lab/Exp-7/Plant Disease/Test', target_size=(126,126), class_mode="categorical")

from keras import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense

model = Sequential()
model.add(Conv2D(32,(5,5),padding="same",input_shape=(126,126,3),activation="relu"))
model.add(MaxPooling2D(2,2))
model.add(Conv2D(32,(5,5),padding="same",activation="relu"))
model.add(MaxPooling2D(2,2))
model.add(Conv2D(64,(5,5),padding="same",activation="relu"))
model.add(MaxPooling2D(2,2))
model.add(Flatten())
model.add(Dense(36, activation="relu"))
model.add(Dense(3,activation="softmax"))

model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=['accuracy'])
hist = model.fit(train_data, validation_data=test_data, epochs=2)

test_loss,test_acc = model.evaluate(test_data)
# print(test_loss)
print(test_acc)

# Plotting accuracy and validation accuracy
plt.plot(hist.history['accuracy'], label='Accuracy')
plt.plot(hist.history['val_accuracy'], label='Val Accuracy')
plt.legend(); plt.show()

# Plotting loss and validation loss
plt.plot(hist.history['loss'], label='Loss')
plt.plot(hist.history['val_loss'], label='Val Loss')
plt.legend(); plt.show()
