# Color channels and Histogram (*4th March*)

### Color channel
- **RGB** Primary Colors namely Red, Green, Blue

- **CMYK** Secondary colors gained by mixed primay colors(Red+Blue = Magenta, Red+Green = Yellow, Blue+Green = Cyan, Red+Green+Blue = Keyline(Black))

- **HSV** models how color appear under light
1. Hue describes dominant wavelength (primary colors)
2. Saturation defines the brilliace and intensity of color
3. Value refers to the darkness or lightness of color

### Histogram 

Histogram describes the count of a number for a given data. For example, for image, there is pixel value for every pixel. When normalized, the range of the pixel value is taken as $0-255$ for 8 bit system ($2^8 = 256$). In the task above, source image is converted into GrayScale and HSV color channels. Then, histogram of RBG color channel and Grayscale channel is plotted.

### Functions used

`cv::cvtColor (<source-image>, <destination-image>, <color-space-conversion-code>, )`

`cv::calcHist(const Mat * images, int nimages, const int* channels, InputArray 	mask, OutputArray hist, int dims, const int* histSize, const float** ranges, bool uniform = true, bool 	accumulate = false)	`

