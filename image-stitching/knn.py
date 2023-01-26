import numpy as np 

class kNN:
    def __init__(self, neighbours):
        self.neighbours = neighbours

    def euclidean_distance(self, row_1, row_2):
        distance = 0.0
        for i in range(len(row_1)):
            distance += (row_1[i] - row_2[i])**2
            
        return np.sqrt(distance)
    
    def k_NN(self, train, test_row):
        distances = []
        
        for i in range(len(train)):
            dist = self.euclidean_distance(test_row, train[i])
            distances.append((train[i], dist, i))
        distances.sort(key=lambda tup: tup[1])
        
        neighbors = []
        distan = []
        index = []
        
        for i in range(self.neighbours):
            neighbors.append(distances[i][0])
            distan.append(distances[i][1])
            index.append(distances[i][2])
        
        return [neighbors, distan, index]
        
