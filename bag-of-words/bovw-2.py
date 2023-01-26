import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import sys
import glob
import pickle

from sklearn import cluster

import kmeans

def abs_dist(TF1, TF2):
    diff = 0
    for i in range(len(TF1)):
        diff += abs(TF1[i] - TF2[i])   
    return diff

path  = str(sys.argv[1] + '*' + sys.argv[2])

n = int(input("Enter 0 for Sklearn KMeans, 1 for self-written KMeans: "))

n_cluster = int(input("Enter the number of cluster: "))

nfeatures = int(input("Enter the number of features: "))

images = []
for filename in glob.glob(path):
    im = cv.imread(filename)
    images.append(im)

## Step 1: Extract the keypoint features and descriptor

sift = cv.SIFT_create(nfeatures = nfeatures)
current_img = images[0]
keypoints, descriptors = sift.detectAndCompute(current_img, None)

for img in images[1:]:
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

    kp, des = sift.detectAndCompute(gray,None)
    descriptors = np.append(descriptors, des, axis = 0)

# Step 2: Cluster 
if (n == 0):

    # KMeans from sklearn

    km = cluster.KMeans(n_clusters=n_cluster, random_state = 0)
    km.fit(descriptors)

elif (n == 1):
    # Self Written KMeans
    
    km = kmeans.KMeans(n_centroids=n_cluster)
    km.fit(descriptors)

# Step 3: Creating Feature Vector from Histogram that will be our Visual Vocabulary 

feature_vectors = []
imagestemp = images

for img in imagestemp:
        
    img = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    sift = cv.SIFT_create(nfeatures = nfeatures)
    kp, des = sift.detectAndCompute(img,None)

    predict_kmeans = km.predict(des)

    hist, bin_edges = np.histogram(predict_kmeans, bins = np.arange(n_cluster + 1))
    feature_vectors.append(hist)

feature_vectors = np.array(feature_vectors)

# Step 4: Creating Weight Matrix from TF-IDF

sum_feature = []

for i in range(feature_vectors.shape[0]):
    temp = 0
    temp = sum(feature_vectors[i,:])
    sum_feature.append(temp)

sum_feature = np.array(sum_feature)

N = len(images)
IDF = np.zeros((n_cluster,1))

temp1 = np.zeros((n_cluster,1))

for i in range(n_cluster):
    temp2 = 0
    for j in range(len(images)):
        if (feature_vectors[j,i] != 0):
            temp2 += 1
    temp1[i] = temp2

for i in range(n_cluster):
    IDF[i] = np.log(N / temp1[i])

TF = np.zeros((len(images),n_cluster))

for i in range(len(images)):
    for j in range(n_cluster):
        TF[i,j] = feature_vectors[i,j] / sum_feature[i] 

weights = np.zeros((len(images),n_cluster))

for i in range(len(images)):
    for j in range(n_cluster):
        weights[i,j] = TF[i,j] * IDF[j] # eliminates weak, redundant features

# Step 5: Testing on Images 

test_path = input("Enter the path of the image to be searched in database: ")

testpath = str(test_path)
test_image = cv.imread(testpath)
test_image1 = cv.cvtColor(test_image,cv.COLOR_BGR2GRAY)

sift = cv.SIFT_create(nfeatures = nfeatures)
kp1, des1 = sift.detectAndCompute(test_image1,None)

test_predict = km.predict(des1)
hist_test, bin_edges1 = np.histogram(test_predict, bins = np.arrange(n_cluster + 1))

sum_feature_test = sum(hist_test)

TF_test = []

for j in range(n_cluster):  # Creating an array of TF
    temp = hist_test[j] / sum_feature_test
    TF_test.append(temp)
    
TF_test = np.array(TF_test)

difference = np.zeros(len(images))
for i in range(len(images)):
    d = abs_dist(TF_test, weights[i,:])
    difference[i] = d

diff = np.argmin(difference) # chosing the image with the least difference in TF
cv.imshow('Input Image', test_image)
cv.imshow('Image Found from Database', images[diff])
cv.waitKey(0) 