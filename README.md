# canonical-coloring

Implementation of Berkholz, Bonsma, and Grohe's O((m+n)log n) algorithm for computing a canonical
coloring (or coarsest equitable partition) for digraphs. Our implementation is a bit less efficient
as it uses a vector of sets to represent the current partition.

Source code includes a simpe class for digraphs to represent the graph passed to the algorithm, and
two exacutables: ```simple_test```, and ```graphs_DIMACS```. The first computes the canonical partition for
two simple graphs with initial colorings. The second is a general tool computes the canonical partition
for the graphs listed in a file given as arguments. Each file in the list must contain a graph in DIMACS
format. A repository of such files can be found [here.](https://pallini.di.uniroma1.it/Graphs.html)

References:

Berkholz, Bonsma, and Grohe. Tight Lower and Upper Bounds for the Complexity of Canonical Colour Refinement. 2015. arXiv:1509.08251

