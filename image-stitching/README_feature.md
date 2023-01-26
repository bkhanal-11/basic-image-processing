# Keypoint Detection and Feature Extraction

### Requirement

1. Region extraction needs to be repeatable and accurate
     - Invariant to translation, rotation, scale changes
     - Robust or covariant to affine transformation
     - Robust to lighting variations, noise, blur, quantization
2. Locality
     - Features are local, therefore robust to occlusion and clutter
3. Quantity
     - Sufficient region to cover the object
4. Distinctiveness
     - The region should contain "interesting" structure
5. Efficiency
     - Close to real-time performance

## Four key stages

1. Feature Detection

Each image is searched for locations that are likely to match well in other images.

2. Feature Description

Each region around detected keypoint locations is converted into a more compact and stable (invariant) descriptor that can be matched against other descriptor.

3. Feature Matching

We efficiently search for likely matching candidates in other image.

4. Feature Tracking 

As an alternative to the third stage that only searches a small neighborhood around detected feature and is therefore more suitable for video processing.

## Feature Detection

For a keypoint localization, the main objective is to have a repeatable detection, precise localization and interesting content. We look for two dimensional signal change. For that we try to find corners as they are repeatable and distinctive. In the region around a corner, image gradient has two or more dominant directions.

1. Harris Detector Formulation

Change in intensity for a shift $[u, v]$ is given as

```math
E(u,v) = \sum_{x,y} w(x,y) [I(x+u, y+v) - I(x,y)]
```   

where $w(x,y)$ is a window function (can be a Uniform or Gaussian) which is used to detect corners, $I(x+u, y+v)$ is shifted intensity and $I(x, y)$ is intensity. The expression above can also be written as

```math
E(u,v) = \begin{bmatrix} u && v \end{bmatrix} M \begin{bmatrix} u \\ v \end{bmatrix}
```

where $M$ is $2 \times 2$ auto correlation matrix computed from Image derivatives.


```math
M = \sum_{x,y} w(x,y) \begin{bmatrix} {I_{x}}^2 && I_{x}I_{y} \\ I_{x}I_{y} && {I_{y}}^2 \end{bmatrix}
```

where $I_{x}, I_{y}$ are derivative of the image w.r.t x and y.


**Window Function**

1. Uniform Window

     Sum over square window

```math
M = \sum_{x,y} \begin{bmatrix} {I_{x}}^2 && I_{x}I_{y} \\ I_{x}I_{y} && {I_{y}}^2 \end{bmatrix}
```

*not rotation invariant*

2. Smooth with Gaussian

     Gaussian already performs weighted sum

```math
M = g(\sigma) \ast \begin{bmatrix} {I_{x}}^2 && I_{x}I_{y} \\ I_{x}I_{y} && {I_{y}}^2 \end{bmatrix}
```

Hence Harris Detector can be summarized in following steps:

1. Image Derivatives ($I_{x}, I_{y}$)

2. Square of derivatives (${I_{x}}^2, {I_{y}}^2$)

3. Gaussian Filter

```math
M (\sigma_{I}, \sigma_{D})  = g(\sigma_{I}) \ast \begin{bmatrix} {I_{x}}^2 (\sigma_{D}) && I_{x}I_{y} (\sigma_{D}) \\ I_{x}I_{y} (\sigma_{D}) && {I_{y}}^2 (\sigma_{D}) \end{bmatrix}
```

4. Cornerness Function - two strong eigen values

```math
\theta  = det[M(\sigma_{I}, \sigma_{D})] - \alpha [trace(M(\sigma_{I}, \sigma_{D}))]^2
```
```math
= g({I_{x}}^2)g({I_{y}}^2) - [g(I_{x}) g(I_{y})]^2 - \alpha [g({I_{x}}^2)+g({I_{y}}^2)]^2
```

5. Perform non-maximum supression

*Harris detector is translation and rotation invariant but not scale invariant.*

Hence, we need to look for scale invariant region selector (detector). A common approach is to select a function which is scale invariant and take a local maximum of this function. There are two candidate function for this purpose.

1. Laplacian

```math
L = \sigma^2 (G_{xx}(x,y,\sigma)+G_{yy}(x,y,\sigma))
```

2. Difference of Gaussian (**DoG**)

```math
DoG = G(x,y,k\sigma) - G(x,y,\sigma)
```

where $G(x,y,\sigma) = \frac{1}{\sqrt{2\pi}\sigma} e^{- \frac{x^2 + y^2}{2 \sigma^2}}$

## Feature Description

Given two images of the same scene with a large scale difference between them, we have to find same interest points independently in each image. For that we need to search for maxima of suitable functions in scale and in space i.e **Scale Invariant Detectors**. We have two methods for that. **Harris-Laplacian** maximizes laplacian over scale and does measurement of corner response over the image. While **SIFT** maximizes Difference of Gaussian over scale and space.

## SIFT (Scale Invariant Feature Transform)

We need a point descriptor that is invariant and distinctive. Given a key point and its scale from DoG, we will select a characteristic orientation for keypoint (based on the most prominent gradient). Then we will describe all features relative to this orientation which will cause feature to be rotation invariant.

### Steps for SIFT

1. Use the blurred image associated with the keypoint scale

2. Take image gradients over the keypoint neighborhood

3. To become rotation invariant, rotate the gradient direction and location by keypoint orientation

4. Create array of orientation histogram ($4 \times 4$)

5. Put the rotated gradients into their local oriental histogram

6. 8 oriental bins per histogram and a $4 \times 4$ histogram array yields $ 8 \times 4 \times 4 = 128$ numbers

7. SIFT descriptor is a length $128$ vector which is invariant to rotation and scale

8. We compare each vector from Image A to each vector from Image B to find matching key point

**Adding robustness to illumination changes**

- Since descriptor is made up of gradient, it is already invariant to brightness

- Higher-contrast photo will increase the magnitude of gradient linearly, hence normalize the vector

- Very large image gradient are usually due to unreliable 3D illumination, hence clamp all the values in vector to be $\leq 0.2$ (experimentally tested) and normalize again

## Application

### Image Stitching

a) Detect Keypoints

b) Build the SIFT descriptor

c) Match SIFT descriptor (feature descriptor have to be designed so that Euclidean distance in feature space can directly be used for ranking potential matched)

d) Fitting the transformation

