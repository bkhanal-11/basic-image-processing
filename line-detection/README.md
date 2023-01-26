# Line Detect Algorithm

Hough Transformation was used for line detection in a video. The following steps were followed:

1. `VideoCapture(<path>)` was used to read video from given path.
2. Every frame in the video was extracted and converted into gray scale.
3. Edges were extracted using Canny Edge Detection method from the Gray Scaled Image.
4. Hough Line Transformation was applied in Canny Image.
5. Line extracted from Hough Line was plotted in the original frame.


### Important Functions used

`HoughLine(<input-canny-image>, <output-lines>, <dist-res>, <angle>, <threshold>)`

`lines(<output-image>, <point1>, <point2>, <color>, <thickness>, <line-type>)`

The basic idea behind Hough Transformation for line is that every line in cartesian coordinate system can be converted into polar coordinate. Hough Transform keeps track of the intersection between curves of every point in the image. If the number of intersections is above some threshold, then it declares it as a line with the parameters $`\theta , r_\theta `$ of the intersection point.  
