import numpy as np
import sys
import cv2 as cv
import glob
from PIL import Image 

import ransac, knn, blend

path  = str(sys.argv[1] + '*' + sys.argv[2])

# path = str('data/' + '*' + '.jpg')

print("Reading Images...")

images = []
for filename in glob.glob(path):
    im = cv.imread(filename)
    images.append(im)
if (len(images) == 0):
    print("Error reading Images!")
    sys.exit()

print("Detecting Features and Matches...")

sift = cv.SIFT_create(nfeatures = 500)
keypoints = []
points = []
descriptors = []

for img in images:
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

    kp, des = sift.detectAndCompute(gray,None)
    pts = [p.pt for p in kp]
    points.append(pts)
    keypoints.append(kp)
    descriptors.append(des)

k = knn.kNN(neighbours = 2)

matches = []

for i in range(len(descriptors[1])):
    temp1, temp2 ,temp3 = k.k_NN(descriptors[0], descriptors[1][i])
    matches.append((i, temp2, temp3))

# filtering out the best matches
good_matches = []

ratio = 0.85

for i in range(len(matches)):
    if matches[i][1][0] < ratio * matches[i][1][1]:
        good_matches.append((matches[i][0], matches[i][1][0], matches[i][2][0]))

# sort according to minimum distance
good_matches.sort(key=lambda tup: tup[1])

# converting cv.keypoints into plain coordinates
img1_kp = []
img2_kp = []

for i in range(len(good_matches)):
    temp1 = points[0][good_matches[i][2]]
    temp2 = points[1][good_matches[i][0]]
    
    img1_kp.append(temp1)
    img2_kp.append(temp2)

img1_kp = np.array(img1_kp)
img2_kp = np.array(img2_kp)

print("Finding Homography...")

RN = ransac.RANSAC(threshold = 20, iterations = 10000)

H = RN.cal_RANSAC(img2_kp, img1_kp)

print("Stitching Two Images...")

st = blend.Blend()

final_image = st.attach(images[0], images[1], H)

final_result = final_image.astype('uint8')
img = Image.fromarray(final_result, 'RGB')

final_image = np.array(img)    
final_image = cv.cvtColor(final_image, cv.COLOR_RGB2BGR)
cv.imshow('Stitched Image', final_image)
cv.waitKey(0)