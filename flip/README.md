# Image Flip

Image is consists of pixel values. In order to flip an image, we need to reverse the sequence of pixel by columns or rows depending on the type of flip (horizontal or vertical).

## Horizontal Flip

In simple matrix formulation, horizontal flip can be demonstrated as follow:

$`\begin{bmatrix}
a & b & c & d & e \\
f & g & h & i & j \\
k & l & m & n & o\\
p & q & r & s & t
\end{bmatrix}`$
$`\to`$
$`\begin{bmatrix}
e & d & c & b & a \\
j & i & h & g & f\\
o & n & m & l & k\\
t & s & r & p & q
\end{bmatrix}`$

Here, the matrix value of columns have been reversed which gives us a horizontal flip.

## Vertical Flip

In simple matrix formulation, vertical flip can be demonstrated as follow:

$`\begin{bmatrix}
a & b & c & d & e \\
f & g & h & i & j \\
k & l & m & n & o\\
p & q & r & s & t
\end{bmatrix}`$
$`\to`$
$`\begin{bmatrix}
p & q & r & s & t \\
k & l & m & n & o\\
f & g & h & i & j\\
a & b & c & d & e
\end{bmatrix}`$

Here, the matrix value of rows have been reversed which gives us a vertical flip.
