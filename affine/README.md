## Affine Transformation

In Affine Transformation, the only property that is preserved is that the parallel lines stay parallel.
In 2D, it can be represented as follow.

```math
x' = \begin{bmatrix} a_{00} && a_{01} && a_{02} \\ a_{10} && a_{11} && a_{12}\end{bmatrix} \bar{x}
```

where $`A = \begin{bmatrix} a_{00} && a_{01} && a_{02} \\ a_{10} && a_{11} && a_{12}\end{bmatrix}`$ is an arbitrary $`2 * 3`$ matrix. 

In general the following transformations can be considered affine transformation:

## Translation

Translation preserves almost every property of an object. It just relocates an object preserving dimension and orientation.

A simple 1D, translation can be represented as $`x' = x + t`$ where $`t`$ is amount to be translated and can be negative.

```math
x' = {\begin{bmatrix} I && t \end{bmatrix}}_{2*3} \bar{x}
```

This is 2D representation of translation. Here, $`I`$ is a $`2*2`$ identity matrix, $`t`$ is 2D translation coordinate and $`\bar{x}`$ is a homogeneous vector.
`
## Euclidean Transformation

Euclidean Transformation, also known as *rigid transformation*, is combination of translation and rotation. Hence, it preserves length and shape of an object.

A simple 1D, euclidean tranformation can be represented as $`x' = Rx + t`$ 

where $`R`$ is Rotation matrix and can be written as 
$`R = \begin{bmatrix} cos \alpha &&-sin \alpha \\ sin \alpha && cos \alpha \end{bmatrix}`$ where $`\alpha`$ is an angle of rotation.

Like in translation, the euclidean transformation can be represented as
```math
x' = {\begin{bmatrix} R && t \end{bmatrix}}_{2*3} \bar{x}
```

$`R`$ is also an orthonormal rotation matrix and has properties $`RR^{T} = I`$ and $`|R| = 1`.

## Similarity

Similarity, also known as *scaled transformation*, is just scaled euclidean transform. The rotation is scaled followed by translation. Hence, it only preserves angle between the lines.

A simple 1D, similarity can be represented as $`x' = sRx + t`$ where $s$ is a scalar. 

```math
x' = {\begin{bmatrix} sR && t \end{bmatrix}}_{2*3} \bar{x}
```

This is the 2D representation of similarity.

## Shear

A shear transformation can be represented as following matrix:


```math
x' = \begin{bmatrix} 1 && s_{x} && 0 \\ s_{y} && 1 && 0\end{bmatrix} \bar{x}
```

where $`s_{x}, s_{y}`$ are shearing coefficient in x and y direction respectively.
