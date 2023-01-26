import numpy as np
from numpy import linalg as LA 

class RANSAC:
    def __init__(self, threshold, iterations):
        self.threshold = threshold
        self.iterations = iterations
    
    def homography(self, pts1, pts2):
        
        temp = len(pts1)
        A = np.zeros((2 * temp, 9))
        index = 0
        
        for i in range(0, temp):
            (a_x, a_y) = pts1[i]
            (b_x, b_y) = pts2[i]
            
            row1 = [-a_x, -a_y, -1, 0, 0, 0, b_x * a_x, b_x * a_y, b_x] # First row 
            row2 = [0, 0, 0, -a_x, -a_y, -1, b_y * a_x, b_y * a_y, b_y] # Second row 

            A[index] = row1
            A[index + 1] = row2

            index += 2

        U, S, Vt = LA.svd(A)
        
        H = np.eye(3)
        H = Vt[-1].reshape(3,3) 
        
        H = H / H[2,2]
        
        return H
    
    def ComputeInliers(self, x, y, H): 

        inlier_indices = []
        y_homo = []
        
        for i in range(len(y)):
            temp = [y[i][0],  y[i][1], 1]
            y_homo.append(temp) 
                        
        y_homo = np.array(y_homo).T
        transformed_y = np.matmul(H, y_homo) 

        norm_x = np.array([transformed_y[0] / transformed_y[2], transformed_y[1] / transformed_y[2]]).T 
        
        for i in range(len(norm_x)):
            if(np.linalg.norm(norm_x[i] - x[i]) <= self.threshold): # check against threshold
                inlier_indices.append(i)
                
        return inlier_indices
    
    def cal_RANSAC(self, x, y):
        H = np.eye(3)
        nBest = 0
        
        inliers_match = []
        
        best_inliers = [] 
        
        for i in range(self.iterations):
            idx = np.random.randint(len(x), size = 4)
            set1 = x[idx,:]
            set2 = y[idx,:]
            
            estimated_H = self.homography(set1, set2)
            
            # Calculate the inliers for the H
            inliers = self.ComputeInliers(x, y, estimated_H)

            # if the number of inliers is higher than previous iterations, update the best estimates
            if len(inliers) > nBest:
                nBest = len(inliers)
                H = estimated_H
                best_inliers = inliers
            
        
        # compute a homography given this set of best inlier matches
        im1_pts = np.empty((len(best_inliers), 2))
        im2_pts = np.empty((len(best_inliers), 2))
        
        for i in range(0,len(best_inliers)):
            m = best_inliers[i]
            
            im1_pts[i] = x[m]
            im2_pts[i] = y[m]
        
        H = self.homography(im1_pts, im2_pts)
        
        return H  