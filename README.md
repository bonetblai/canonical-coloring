# canonical-coloring

Implementation of Berkholz, Bonsma, and Grohe's O((m+n)log n) algorithm for computing a canonical
coloring (or coarsest equitable partition) for digraphs. Our implementation is a bit less efficient
as it uses a vector of sets to represent the current partition.

Source code includes a simpe class for digraphs to represent the graph passed to the algorithm.

References:

Berkholz, Bonsma, and Grohe. Tight Lower and Upper Bounds for the Complexity of Canonical Colour Refinement. 2015. arXiv:1509.08251

