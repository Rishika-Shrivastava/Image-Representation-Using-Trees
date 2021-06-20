# Image-Representation-Using-Trees

### Problem Statement
A binary image is an image in which intensity value of each pixel is either 0 or 1. The value 0 represents the background and 1 represents the foreground pixel, i.e., actual object pixel. 

Consider a binary image/matrix of size (n pixels) X (n pixels)
[n=4m, where m is an integer]. Divide the entire image space into four equal segments recursively. The segments are labelled as A, B, C, D. Each segment is again subdivided into four equal segments and the process continues recursively until each segment contains a single pixel.

Pixels of each segment are labelled in clockwise direction.
We can decide to store the image in memory as a tree. Each node of the tree has four children. A, B, C, D are the four children of the parent node. Each level of segmentation is represented at the same level nodes in the tree. The internal nodes store the labels. The leaves store the intensity value (0/1).
The root is a node representing the complete image/matrix.

### Functionalities
I. Implementing the tree structure for a given image. Each internal node stores the label of the segment. Each leaf node stores the label of the segment, coordinates and pixel intensity value. \
Hint : Knowing the value of “n”, you can determine the number of levels of the tree.

II. Finding the total number of foreground pixels (value 1) in the tree.

III. Implementing an efficient search algorithm to count the number and pairs of disjoint* foreground objects present in the image by traversing the tree.

a. First consider every pixel as an object. So, disjoint pixels to be found in the
original image matrix given. \
b. If we consider an object at any level in the tree as a foreground object, if it
contains a pixel 1 inside (i.e. in its subtree), find the number and pairs of
foreground objects at every level in the tree. \
Note: *Two objects are said to be disjoint if no foreground pixels in the first object is a neighboring pixel of any foreground pixel in the second object.

IV. Traversing the tree to display the image in
a) row wise fashion \
b) column wise fashion \
c) spiral traversal of the given image. \
