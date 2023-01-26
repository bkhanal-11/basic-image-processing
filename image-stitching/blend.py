import numpy as np
import cv2 as cv

class Blend:
    def __init__(self):
       """
       Takes two images and
       homography and stitched them
       """
     
    def attach(self, img1, img2, H):
        height_img1 = img1.shape[0]
        width_img1 = img1.shape[1]
        width_img2 = img2.shape[1]
        final_height = height_img1
        final_width = width_img1 + width_img2

        final_image1 = np.zeros((final_height, final_width, 3))
        final_image2 = np.zeros((final_height, final_width, 3))

        final_image1[0:height_img1, 0:width_img1, :] = img1
        final_image2[0:height_img1, width_img1:, :] = img2

        warped_img1 = cv.warpPerspective(final_image1, H, (final_width, final_height))

        final_image2[0:height_img1, 0:width_img1, :] = warped_img1[0:height_img1, 0:width_img1, :]

        rows, cols = np.where(final_image2[:, :, 0] != 0)
        min_row, max_row = min(rows), max(rows) + 1
        min_col, max_col = min(cols), max(cols) + 1
        final_result = final_image2[min_row:max_row, min_col:max_col, :]

        return final_result