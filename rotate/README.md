# Image Rotation

Rotation of Image involves rotating the pixel by given angle and the updating those new pixel with the pixel values from original matrix (image).

A simple rotation matrix is given as:

```math
\begin{bmatrix}
cos \alpha && -sin \alpha \\
sin \alpha && cos \alpha 
\end{bmatrix}
```
where $\alpha$ is the angle of rotation.

For a rotation about a point $(p,q)$, we have:

```math
\begin{bmatrix}
x' \\
y'
\end{bmatrix} = 
\begin{bmatrix}
cos \alpha && -sin \alpha \\
sin \alpha && cos \alpha
\end{bmatrix}
\begin{bmatrix}
x \\
y
\end{bmatrix} +
\begin{bmatrix}
p \\
q                       
\end{bmatrix}
```

Since for an image the new pixels need to be defined, we do an affine warp transformation of rotation which can be seen as follow. 

We modify the rotation matrix as:

```math
\begin{bmatrix}
cos \alpha && sin \alpha && (1-cos \alpha)*p - sin \alpha * q\\
-sin \alpha && cos \alpha && sin \alpha *p + (1 - cos \alpha) *q
\end{bmatrix}
```

and we feed in this rotation matrix to affine transformation as dest $(x, y)$ = src $(M_{11}x+M_{12}y+M_{13},M_{21}x+M_{22}y+M_{23})$

This updates the new rotated cooridinate (pixel) with the original pixel values.
