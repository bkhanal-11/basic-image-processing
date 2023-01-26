# Convolution of Images

A convolution is an integral that expresses the amount of overlap of one function as it is shifted over another function. For Images, it is a filtering operation.

Mathmatically, 2D convolution can be formulated as follow.

```math
f[n,m] \ast h[n,m] = \sum_{k = -\infty}^{\infty} \sum_{l = -\infty}^{\infty} f[k,l] h[n-k, m-l]

```

This represents discrete form of integration. For convolution, $`f[n,m]`$ is image and $`h[n,m]`$ is filter (kernel).

### Padding

Everytime a convolution is applied, following problem arises:

1. Every time after convolution operation, original image size getting shrinks, as we have seen in above example six by six down to four by four and in image classification task there are multiple convolution layers so after multiple convolution operation, our original image will really get small but we don’t want the image to shrink every time.

2. The second issue is that, when kernel moves over original images, it touches the edge of the image less number of times and touches the middle of the image more number of times and it overlaps also in the middle. So, the corner features of any image or on the edges aren’t used much in the output.

The Zero-padding pads (adds) the input with zeros so that the output size from the convolution is exactly the same as the input size. For example, if zero padding is applied to an input tensor of dimension $`5 \times 5`$ with filter size of $`3 \times 3`$, the input tensor will be incremented by 2 dimensions each direction with '0' as the outer tensor value so that when the convolution is done, the output will be $`5 \times 5`$.

### Strides

The strides is the step-size used by the layer to move the filters ($`h[n,m]`$) across the input. Increasing the strides therefore reduces the size of the output tensor. For example, when strides of '2' is applied, the height and width of the output tensor will be half the size of the input tensor.

"Stride" is something completely different then width and height of an image; it's a concept related to the logical storage layout (memory addressing) of the image data array on the physical memory accessed by a program, and not to the geometric properties of the image.

Stride means "the logical memory address distance between two successive pixels of the image on a given axis" (it's the value that should be added to the pointer (which points into the buffer of the image data on memory) that would then access the data of the next sample on the chosen image axis).

### References
1. [Strides in Image Processing](https://dsp.stackexchange.com/questions/40273/why-do-digital-images-use-the-concept-of-stride)
2. [Convolution](https://stackoverflow.com/questions/13981699/opencv-how-does-the-filter2d-method-actually-work)
3. [Pooling](https://medium.com/analytics-vidhya/convolution-padding-stride-and-pooling-in-cnn-13dc1f3ada26)
4. Generative Deep Learning - David Foster
