import pandas as pd
import numpy as np
import sklearn.datasets
import sklearn.utils
import os
import csv
import sys
import shutil
import serial
import time
from collections import namedtuple
from os import environ, listdir, makedirs
from os.path import dirname, exists, expanduser, isdir, join, splitext

def main():
  # Load scikit's random forest classifier library
  from sklearn.ensemble import RandomForestClassifier

  # Set random seed
  np.random.seed()

  # Create an object called trainingSignals with the training data
  trainingSignals = loaddata()

  # Create a dataframe
  df = pd.DataFrame(trainingSignals.data, columns=trainingSignals.feature_names)

  #Populate the class names next to the variable data
  df['letters'] = pd.Categorical.from_codes(trainingSignals.target, trainingSignals.target_names)

  #the fun way of test data (uniform dist at 75%)
  df['is_train'] = np.random.uniform(0, 1, len(df)) <= .75

  # Create two new dataframes, one with the training rows, one with the test rows
  train, test = df[df['is_train']==True], df[df['is_train']==False]
  # Show the number of observations for the test and training dataframes
  print('Number of observations in the training data:', len(train))
  print('Number of observations in the test data:',len(test))

  # Create a list of the feature column's names
  features = df.columns[:8]

  #need to integerize the Letter Names of the classes (0-25 A-Z)
  y = pd.factorize(train['letters'])[0]

  # Create a random forest Classifier. By convention, clf means 'Classifier'
  clf = RandomForestClassifier(n_jobs=4, random_state=0)

  # Train the Classifier on the letter data
  clf.fit(train[features], y)

  #Predict a character
  preds = trainingSignals.target_names[clf.predict(test[features])]

  print(pd.crosstab(test['letters'], preds, rownames=['Actual Letters'], colnames=['Predicted Letters']))

  #From here on, loop forever reading data from the serial to use as "test" data
  ser = serial.Serial('/dev/cu.HC-06-DevB', 9600, timeout=0)
  while 1:
    temp = ser.readline()
    tempArr = temp.split(",")
    tempArr = tempArr[:len(tempArr)-1]
    if len(tempArr) != 8:
        time.sleep(1)
        continue;
    x = np.array(tempArr)
    serialData = x.astype(np.float)
    d = {"Thumb": serialData[0].tolist(), "Index1": serialData[1].tolist(), "Index2": serialData[2].tolist(),
        "Middle1": serialData[3].tolist(), "Middle2": serialData[4].tolist(), "Ring1": serialData[5].tolist(),
        "Ring2": serialData[6].tolist(), "pinky": serialData[7].tolist()}

    '''d = {"Thumb": [serialData[0]], "Index1": [serialData[1]], "Index2": [serialData[2]],
        "Middle1": [serialData[3]], "Middle2": [serialData[4]], "Ring1": [serialData[5]],
        "Ring2": [serialData[6]], "pinky": [serialData[7]]}

    d = {"Thumb": [float(tempArr[0])], "Index1": [float(tempArr[1])], "Index2": [float(tempArr[2])],
        "Middle1": [float(tempArr[3])], "Middle2": [float(tempArr[4])], "Ring1": [float(tempArr[5])],
        "Ring2": [float(tempArr[6])], "pinky": [float(tempArr[7])]}'''
    dataDF = pd.DataFrame(data=serialData)
    dataDF = dataDF.transpose()
    preds = trainingSignals.target_names[clf.predict(dataDF)]
    print preds[0]
    time.sleep(0.5)

def loaddata():
  """df=pd.read_csv('binary_train.csv', sep=',',header=None)
  print(df.values)
  temp = np.hsplit(df.values,np.array([3,6]))

  returnData = {'data': np.array(temp[0]),'targets':temp[1]}
  print(returnData['data'])
  print(returnData['targets'])"""
  fdescr = "ASL glove training data"
  module_path = dirname(__file__)
  data, target, target_names = load_data(module_path, 'binary_train.csv')
  return sklearn.datasets.base.Bunch(data=data, target=target,
                 target_names=target_names,
                 DESCR=fdescr,
                 feature_names=['Thumb', 'Index1', 'Index2', 'Middle1', 'Middle2', 'Ring1', 'Ring2',
                                'pinky'])

def load_data(module_path, data_file_name):
    """Loads data from module_path/data/data_file_name.
    Parameters
    ----------
    data_file_name : String. Name of csv file to be loaded from
    module_path/data/data_file_name. For example 'wine_data.csv'.
    Returns
    -------
    data : Numpy Array
        A 2D array with each row representing one sample and each column
        representing the features of a given sample.
    target : Numpy Array
        A 1D array holding target variables for all the samples in `data.
        For example target[0] is the target varible for data[0].
    target_names : Numpy Array
        A 1D array containing the names of the classifications. For example
        target_names[0] is the name of the target[0] class.
    """
    with open(join(module_path, 'data', data_file_name)) as csv_file:
        data_file = csv.reader(csv_file)
        temp = next(data_file)
        n_samples = int(temp[0])
        n_features = int(temp[1])
        target_names = np.array(temp[2:])
        data = np.empty((n_samples, n_features))
        target = np.empty((n_samples,), dtype=np.int)

        for i, ir in enumerate(data_file):
            data[i] = np.asarray(ir[:-1], dtype=np.float64)
            target[i] = np.asarray(ir[-1], dtype=np.int)

    return data, target, target_names


main()
temp = loaddata()
"""print(temp.data);"""
