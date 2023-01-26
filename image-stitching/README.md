# Image Stitching

In order to stitch two (or more) images together, we need to follow follow steps:

1. Compute keypoints and their respective descriptors of features for both images using SIFT (or SURF, ORB)

2. Compute distances between every descriptor (keypoint) in one image and every descriptor in other image using k-NN algorithm

3. Select the top '**m**' matches for each descriptor of an image

4. Run RANSAC algorithm to estimate homography

5. Warp to align for stitching and stitch

## k-NN algorithm

k-NN is a supervised machine learning algorithm, non-parametric, easy to implement, and used for both the classification and regression problem.

Similar inputs are defined by k-NN as those objects that are clode to one another (have minimum distance). As they are close to each other, they have the same classes/labels/outputs. For measuring distance we can use **Minkowski Distance**.

```math
d_{minkowski} (p,q) = (\sum_{i=1}^{n} {|p_{i} - q_{i}|}^{a})^{\frac{1}{a}}, a \geqslant 1
```

It is a generalized form of finding distance between two points $`p`$ and $`q`$. If $`a = 2`$, it is called **Euclidean Distance**, if $`a = 1`$, it is called **Manhattan Distance** and for $`a = \infty`$, it is called **Chebyshev Distance** which gives distance as the greatest difference between elements i.e.

```math
d_{chev} (p,q) = \underset{i}{\mathrm{max}} |p_{i} - q_{i}|
```

## Random Sampling Consensus (RANSAC)

RANSAC is an iterative method to estimate parameters of a mathematical model from a set of observed data that contains outliers when outliers are to be accorded no influence on the vlaues of the estimate.

RANSAC fits $`N`$ models using different random sample $`S`$ of the whole available data each time. Then, for ach model it evaluates its performance ($`P`$) (i.e. number of inliers or outliers) and chooses the best one. Least square method can be used to find model parameters. 

```math
\underset{\theta}{\mathrm{min}} \sum_{i} (y_{i} - \theta^{T} x_{i})^{2}
```

**Algorithms**

1. **Sample** (randomly) the number of points required to fit the model

2. **Solve** for model parameter using the sample

3. **Score** by the fraction of inliers within a preset threshold of the model

Repeat 1-3 until the best model is found with high confidence.