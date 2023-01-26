import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import sys
import glob
import pickle

from sklearn import cluster

import kmeans

def return_intersection(hist_1, hist_2):
    intersection = 0
    for i in range(len(hist_1)):
        intersection += ((hist_1[i] - hist_2[i])**2) / (hist_1[i] + hist_2[i])
        
    return intersection

path  = str(sys.argv[1] + '*' + sys.argv[2])

n = int(input("Enter 0 for Sklearn KMeans, 1 for self-written KMeans: "))

n_cluster = int(input("Enter the number of cluster: "))

images = []
for filename in glob.glob(path):
    im = cv.imread(filename)
    images.append(im)

## Step 1: Extract the keypoint features and descriptor

sift = cv.SIFT_create(nfeatures = 100) # 100 strongest feature
current_img = images[0]
keypoints, descriptors = sift.detectAndCompute(current_img, None)

for img in images[1:]:
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

    kp, des = sift.detectAndCompute(gray,None)
    descriptors = np.append(descriptors, des, axis=0)

# Step 2: Cluster 
if (n == 0):

    # KMeans from sklearn

    km = cluster.KMeans(n_clusters=n_cluster, random_state=0)
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
    sift = cv.SIFT_create(nfeatures = 100)
    kp, des = sift.detectAndCompute(img,None)

    predict_kmeans = km.predict(des)
    #calculates the histogram
    hist, bin_edges = np.histogram(predict_kmeans, bins = n_cluster)
    #histogram is the feature vector
    feature_vectors.append(hist)

test_path = input("Enter the path of the image to be searched in database: ")

testpath = str(test_path)
test_image = cv.imread(testpath)
test_image1 = cv.cvtColor(test_image,cv.COLOR_BGR2GRAY)

sift = cv.SIFT_create(nfeatures = 100)
kp1, des1 = sift.detectAndCompute(test_image1,None)

test_predict = km.predict(des1)
hist1, bin_edges1 = np.histogram(test_predict, bins = n_cluster)

# Step 4: Comparing histogram of test image and images from database

results = np.zeros(len(images))
for i in range(len(images)):

    d = return_intersection(hist1, feature_vectors[i])
    results[i] = d

sim = np.argmin(results) # chosing the image with the least difference in histogram

cv.imshow('Input Image', test_image)
cv.imshow('Image Found from Database', images[sim])
cv.waitKey(0)