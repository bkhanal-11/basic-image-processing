#Import dependecies
import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt
from random import sample, seed

class KMeans:
	def __init__ (self, n_centroids, threshold = 0.001, epoch = 100, random_state = None):
		"""
			n_centriods : number of codebook vectors
			threshold 	: for checking changes between old and new codebook vectors
			epoch 		: maximum number of iterations
		"""

		self.n_centroids = n_centroids
		self.clusters = None 
		self.centroids = None
		self.threshold = threshold
		self.epoch = epoch
		self.random_state = random_state
		self.name = 'kmeans'	

	def cost(self, X):
	   	#Calculates the average cost!

		cost = 0
		for c in range(self.n_centroids):
			for i in self.clusters[c]:
				cost += LA.norm(X[i] - self.centroids[c])
		return cost/X.shape[0]

	def InitCentroids(self, X):
		if self.random_state:
			np.random.seed(self.random_state)  #Initializing the seed.
			seed(self.random_state) 
			
		row, col = X.shape

		#Option 1
		#indexes = sample(range(row), self.n_centroids)
		#self.centroids = np.array([X[i] for i in indexes])

		#Option 2
		self.centroids = np.random.rand(self.n_centroids, col)


	def findClosestCentroids(self, X):
		row, col = X.shape
		sum_clusters = np.zeros((self.n_centroids,col))
		idx_clusters = [[] for _ in range(self.n_centroids)]

		for i in range(row):
		    shortest = 1e10
		    index = -1
		    x = X[i]
		    for c in range(self.n_centroids):
		        distance = LA.norm(x-self.centroids[c])
		        if distance < shortest:
		            shortest = distance
		            index = c
		    idx_clusters[index].append(i)
		    sum_clusters[index] += x #We don't need to compute sum of clusters again, 
		    							#because we are already calculating here!

		#Removing centroids with empty cluster!
		for i in range(self.n_centroids-1,-1,-1):
		    if not idx_clusters[i]:
		        del idx_clusters[i]
		        sum_clusters = np.delete(sum_clusters, i, 0)
		        self.centroids = np.delete(self.centroids, i, 0)
		        self.n_centroids -= 1

		self.clusters = idx_clusters
		return sum_clusters
	
	#Compute Means
	def computeMeans(self, X, sum_clusters):
	    prev_centroids = np.copy(self.centroids)
	    
	    for c in range(self.n_centroids):
	        n = len(self.clusters[c])
	        self.centroids[c] = sum_clusters[c]/n
	        
	    return prev_centroids
	    
	def checkChanges(self, prev_centroids):
	    for c in range(self.n_centroids):
	        if LA.norm(prev_centroids[c]-self.centroids[c]) > self.threshold:
	            return True
	    return False
	    
	#--------MAIN FUNCTION------#      
	def fit(self, X, y=None):
	    self.InitCentroids(X)

	    for i in range(self.epoch):
	        print("Iteration : " + str(i), end=" | ")
	        
	        sum_clusters = self.findClosestCentroids(X)
	        prev_centroids = self.computeMeans(X, sum_clusters)

	        print("Avg. Cost : " + str(self.cost(X)))
	        if not self.checkChanges(prev_centroids):
	            break

	def transform(self, X):
		X_ = np.zeros((X.shape[0], self.n_centroids))

		for i, x in enumerate(X):
			for j, centroid in enumerate(self.centroids):
				X_[i,j] = LA.norm(x - centroid)

		return X_

	def predict(self, X):
		row, col = X.shape
		idx_clusters = []

		for i in range(row):
		    shortest = 1e10
		    index = 0
		    x = X[i]
		    for c in range(self.n_centroids):
		        distance = LA.norm(x-self.centroids[c])
		        if distance < shortest:
		            shortest = distance
		            index = c
		    idx_clusters.append(index)

		return np.array(idx_clusters)