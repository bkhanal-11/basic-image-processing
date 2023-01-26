# Bag of Words (BoW)

### Challenges in Image Classification

- While matching keypoint to a single pattern, the object we are trying to detect may have several variations

- We may wish to distinguish between different types of objects, associating them with a class

Classical 'brute force' answer to these challenges is to gather a set of search images which represent both the different classes and the variations within each class when exhaustively search for all of the images in a given scene. This is computationally intensive.

Bag of Words (or Bag of Visual Words) presents a more elegant means of distinguishing between classes and accounting for in-class variations whilst levering keypoint matching.

#### Step 1: Extract Keypoint Feature

1. "Visual words" are extracted form each training image using keypoint detection and extraction algorithms (such as SIFT, ORB, SURF)

2. Keypoint detectors use corners, edges and blobs to find low level features in image

3. Keypoint extractor then represent a small patch surrounding each keypoint as vector

#### Step 2: Create the BoW vocabulary

The purpose of the vocabulary is to provide a means of comparing images and distinguishing between them.

This is a limited set of the most common visual words found in the training set.

Here, K-Means Clustering method is used to find a pre-defined number of clusters in the complete training set BoW, resulting in a concise Bow vocabulary. Once vocabulary is established, it forms the $x$-axis of a histogram which can be used to compare and classify images.

#### Step 3: Create BoW Histogram

Having determined the 'bins' of our histogram using vocabulary, we return to our training images and create a histogram for each of our training images. For a given training images, each extracted visual word is mapped to its closest visual word in the BoW vocabulary. The frequency count of the closest visual word in the BoW vocabulary is incremental.

#### Step 4: Train a Linear Support Vector Machine (SVM)

Having generated a BoW histogram for each of our training images, the final step in setting up our image classifier is to train a SVM on the BoW histogram. Once trained, the goal is to take BoW histogram for a new image and correctly classify it.

Having done these, we can take a new image, extract keypoints (visual words), generate a histogram of the images keypoints using BoW vocabulary then present the histogram to the SVM for classifcation.

# K-means Clustering

Generally, the goal in "clustering" is to minimize variance in data given clusters. It gives us an "chicken-egg" problem i.e. 

1. If we knew the *cluster centers*, we could allocate points to groups by assigning each to its closest center.

2. If we knew the group elements, we could get the centers by computing the mean per group.

Best cluster centers are those that minimize Sum of Squared Distance (SSD) between all points and their nearest cluster $c_{i}$,

```math
SSD = \sum_{cluster i} \sum_{x \in cluster i} ( x - {c_{i}}^2)
```

Hence, k-means clustering can be carried out as follow:

1. Initialize ($t = 0$): cluster centers $c_{1}. c_{2},...,c_{k}$
     - commonly used: random initialization 
     - or greedy choose K to minimize residual

2. Compute $\delta^{t}$: assign each point to the closest center
     - Typical distance measure:
          - Euclidean, $dist(x, x') = x^{T}x$
          - Cosine, $dist(x, x') = \frac{x^{T}x}{||x|| ||x'||}$

3. Compute $c^{t}$: update cluster centers as the means of points
```math
c^{t} = \underset{c}{\mathrm{argmin}} \frac{1}{N} \sum_{i}^{N} \sum_{i}^{k} {\delta_{ij}}^{t}({c_{i}}^{t-1}-x_{j})^2
```

4. Update $t=t+1$, repeat Step 2 and 3 until $c^{t}$ does not change anymore

# Term Frequency - Inverse Document Frequency (TF-IDF)

TF-IDF is a popular word embedding technique used in various natural language processing tasks. This can also be implemented for visual databases.

The numerical statistical technique is used to figure out the relevance of any visual word in the image, which is a part of even larger body of image database.

Evident from the name itself, it composes of two terms:

1. Term Frequency (TF)

It measures how many times a visual word appears in an image.

```math
TF = \frac{how many times the "visual word" appears in the image}{total number of "visual words" in the image}
```

2. Inverse Document Frequency (IDF)

It represents how common the visual word is across the image database.

```math
IDF = log(\frac{number of Images in database}{number of images containing the "visual word"})
```

With these calculated, we can calculate the weight of each visual word in each image as

```math
TF-IDF, w(i,j) = TF(i,j) \times IDF(j)
```

where $w(i,j)$ is the weight of $i-th$ visual word (codeword) in image $j$.

# Steps followed for Large Scale Image Search (Attempt 1)

### Step 1

Read all the images from the database

### Step 2

Convert all the images to grayscale, extract their (suppose 100 dominant) keypoints and respective descriptors (SIFT, SURF)

### Step 3

Pass the descriptor to KMeans clustering algorithm with user defined number of clusters

### Step 4

From the set of all the descriptors, predict which descriptor lie in which cluster

### Step 5

Make a histogram of the prediction of descriptor of individual image (this given us histogram of image which tell us how many descriptor lie in respective clusters). This gives us our vocabulary (BoVW)

### Step 6 

For image search, follow the above mentioned step for a single image to be searched (i.e. find keypoints, descriptors, predict the cluster for these descriptor, make histogram). After we get the histogram for test image, we compare (take absolute value) number of features (keypoint) in each cluster for each images from their histogram to number of feature of test image in each cluster and return the image with the least amount of difference.

```math
D(h_{1}, h_{2}) = \sum_{i=1}^{N} \frac{(h_{1}(i) - h_{2}(i))^2}{h_{1}(i) + h_{2}(i)}
```

# Steps followed for Large Scale Image Search (Attempt 2)

### Step 1-5 

Carried out as above
### Step 6 

For image search, follow the above mentioned step for a single image to be searched (i.e. find keypoints, descriptors, predict the cluster for these descriptor, make histogram). After we get the histogram for test image, we compare (take absolute value) number of features (keypoint) in each cluster for each images from their histogram to number of feature of test image in each cluster and return the image with the least amount of difference.
