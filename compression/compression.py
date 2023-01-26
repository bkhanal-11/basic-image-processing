import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from numpy import linalg as LA
from PIL import Image as im
import sys

path = str(sys.argv[1])
img = cv.imread(path)

k_slider_max = 100

ug, sg, vg = LA.svd(img, full_matrices=False)
    
sg = np.diag(sg)

def compress(val):    
    k1 = int(np.floor(val / k_slider_max * sg.shape[0]))

    compressed = np.matmul(ug[:,:k1], np.matmul(sg[:k1,:k1], vg[:k1,:]))
    
    compressed = compressed.astype('uint8')
    compressed = im.fromarray(compressed)
    
    compressed = cv.cvtColor(compressed, cv.COLOR_RGB2BGR)
    
    cv.imshow('Original Image', img)
    cv.imshow('Compressed Image', compressed)

blue = np.array(img[:,:,0])
green = np.array(img[:,:,1])
red = np.array(img[:,:,2])
    
u1, s1, v1 = LA.svd(blue, full_matrices=False)
u2, s2, v2 = LA.svd(green, full_matrices=False)
u3, s3, v3 = LA.svd(red, full_matrices=False)
    
s1 = np.diag(s1)
s2 = np.diag(s2)
s3 = np.diag(s3)

def compress3(val):
    
    k = int(np.floor(val / k_slider_max * s1.shape[0]))
    
    blue = np.matmul(u1[:,:k], np.matmul(s1[:k,:k], v1[:k,:]))
    green = np.matmul(u2[:,:k], np.matmul(s2[:k,:k], v2[:k,:]))
    red = np.matmul(u3[:,:k], np.matmul(s3[:k,:k], v3[:k,:]))
    
    blue = blue.astype('uint8')
    green = green.astype('uint8')
    red = red.astype('uint8')
    blue = im.fromarray(blue)
    green = im.fromarray(green)
    red = im.fromarray(red)
    
    compressed = np.zeros((img.shape[0], img.shape[1], 3))
    
    compressed = im.merge("RGB", (red,green,blue))
    
    compressed = np.array(compressed)
    compressed = cv.cvtColor(compressed, cv.COLOR_RGB2BGR)
    
    cv.imshow('Original Image', img)
    cv.imshow('Compressed Image', compressed)

title_window = 'Compressed Image'
cv.namedWindow(title_window)
trackbar_name = 'Compression Percent: ' 

if (len(img.shape) == 1):
    cv.createTrackbar(trackbar_name, title_window , 0, k_slider_max, compress)
    compress(60)

else:
    cv.createTrackbar(trackbar_name, title_window , 0, k_slider_max, compress3)
    compress3(60)

cv.waitKey(0)