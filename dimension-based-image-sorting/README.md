# STL containers & Algorithms

A container is a holder object that stores a collection of other objects (its element). They are implemented as class templates, which allows a great flexibility in the types supported as elements.

The container manages the storage space for its element and provides member function to access them, either directly or through iterators.

## Sequence containers

Implements data structures which can be accessed sequencially.

- **array**: static contiguous array
- **vector**: dynamic contiguous array
- **deque**: double-ended queue
- **forward_list**: singly-linked list
- **list**: doubly-linked list

## Associative containers

Implements sorted data structure that can be searched quickly [$O(log(n))$ complexity].

- **set**: collection of unique keys, sorted by keys
- **map**: collection of key-value pairs, sorted by keys, keys are unique
- **multiset**: collection of keys, sorted by keys
- **multimap**: collection of key-value pairs, sorted by keys

## Container adopters

Provides a different interference for sequential containers.

- **stack**: adapts a container to provide stack (LIFO data structure)
- **queue**: adapts a container to provide queue (FIFO data structure)
- **priority_queue**: adapts a container to provide priority queue

# Sorting Images

In order to sort image, **vector** container was used for storing images. Two different vectors were created, one to store image and another to store the dimension of images (number of pixels). Then maximum (or minimum depending on desired order) element of dimension was calculated along with the index. The corresponding maximum/minimum "element" in image vector was pushed to new vector giving us a sorted image array.

**input** `./main </images-path/> <.extension>`