# Random Sampling Consensus (RANSAC)

RANSAC is an iterative algorithm which can be used to estimate parameters of a statistical model from a set of observed data which contains outliers. Presented below is a pseudocode of RANSAC for estimating homography.

```c++
H = eye(3,3)
nBest = 0

for int i = 0; i < nIterations; i++ do
     P4 = SelectRandomSubset(P)
     Hi = ComputeHomography(P4)
     nInliers = ComputeInliers(Hi)
     if nInliers > nBest then
          H = Hi
          nBest = nInliers
     end if
end for
```

After all the initialization, the first step is to select four points at random for the set of observations (four per each image) then pass those value to calculate rough estimate of homography.

## Calculating Homography

Homography relates points in first view to point in the second view and since there are no constraints in either view, it is full rank (=3) matrix. Homography is defined upto scale i.e. it can be changed by a non-zero constant without any affect on projective transform. Thus, homography has 8 degree of freedom even though it contains $`9`$ elements ($`3 \times 3`$) matrix i.e. number of unknowns that needs to be solved is $`8`$. We would just need $`4`$ points since each point has $`x`$ and $`y`$ coordinates and there are total $`8`$ unknowns to solve $`H`$ for a unique solution.

Lets assume $`x = \begin{bmatrix} u \\ v \\ 1\end{bmatrix}`$ and $`x' = \begin{bmatrix} x \\ y \\ 1\end{bmatrix}`$ in homogeneous coordinates and $`H = \begin{bmatrix} h_{00} && h_{01} && h_{02} \\ h_{10} && h_{11} && h_{12}\\ h_{20} && h_{21} && h_{22} \end{bmatrix}`$ such that

```math
c \begin{bmatrix} u \\ v \\ 1\end{bmatrix} = 
\begin{bmatrix} h_{00} && h_{01} && h_{02} \\ h_{10} && h_{11} && h_{12}\\ h_{20} && h_{21} && h_{22} \end{bmatrix}
\begin{bmatrix} x \\ y \\ 1\end{bmatrix}
```

By eliminating $`c`$, we can formulate the above equation in the form

```math
Ah = 0
```

where $`A = \begin{bmatrix} -x && -y && -1 && 0 && 0 && 0 && ux && uy && u \\ 0 && 0 && 0 && -x && -y && -1 && vx && vy && v \end{bmatrix}`$ 
and $`h = \begin{bmatrix}h_{0} && h_{1} && h_{2} && h_{3} && h_{4} && h_{5} && h_{6} && h_{7} && h_{8} \end{bmatrix}`$

When there are more than $`4`$ points it would be an over-determined case and hence we have to use **Least Square Solution** to find $`h`$.

```math
min_{h} {||Ah||}_{2}
```

We need to minimize

```math
min_{h} {||Ah||}_{2} s.t. {||h||}_{2} = 1
```

```math
min_{h} {||Ah||}_{2} s.t. (1 - h^{T}h) = 0
```

where $`A \in \R^{m \times 9} , m \geqslant 8`$ and $`h \in \R^{9 \times 1}`$

Using Lagrange, we can write the above optimization as 

```math
min_{h} ({{||Ah||}_{2}}^{2} + \lambda (1 - h^{T}h))
```

Taking partial derivative w.r.t. $`h`$ and setting it to $`0`$

```math
(A^{T}A - \lambda I)h = 0
```

and since $`h \neq 0`$

```math
det(A^{T}A - \lambda I) = 0
```

$`\lambda`$ is one of the eigenvalue of the matrix $`A^{T}A`$ with eigenvector of $`h`$. On **Singular Value Decomposition** of $`A = U \sum V^{T}`$ $`h`$ can be any column of $`V`$, but since we want to minimize $`||Ah||`$, we will take $`h`$ corresponding to the last eigenvalue of $`A^{T}A`$ i.e. last eigenvector of $`A^{T}A`$ or the last column of $`V`$. Now, we can reshape $`h`$ to form $`H`$.