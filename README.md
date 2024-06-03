# canonical-coloring

Implementation of Berkholz, Bonsma, and Grohe's O((m+n)log n) algorithm for computing a canonical
coloring (or coarsest equitable partition) for digraphs. Our implementation is a bit less efficient
as it uses a vector of sets to represent the current partition.

Provided functionality computes the (canonical) quotient matrix Q for the given graph. The entry
Q(i,j] in Q counts the number of edges from a node with color i to nodes of color j, for the
(final) equitable partition.

Source code includes a simpe class for digraphs, and two exacutables: ```simple_test```, and ```graphs_DIMACS```. 
The first computes the canonical partition and quotient matrix for simple graphs with given initial colorings. 
The second is a general tool to compute canonical partitions for the graphs listed in a file given as argument. 
Each file in the list must contain a graph in DIMACS format. A repository of such files can be 
found [here.](https://pallini.di.uniroma1.it/Graphs.html)

The following results were obtained with ```graphs_DIMACS``` on the collection ```dac```
for graphs associated with CNF formulas. In the results, ```n``` and ```m``` are
the number of vertices and edges, respectively, and ```k``` is the number of
colors in the canonical coloring:

```
graphs/dac/2pipe.bliss (n=3575, m=29250) k=1918 color(s) 29.441 millisecond(s)
graphs/dac/3pipe.bliss (n=10048, m=117112) k=5090 color(s) 76.255 millisecond(s)
graphs/dac/4pipe.bliss (n=21547, m=335884) k=10569 color(s) 212.843 millisecond(s)
graphs/dac/5pipe.bliss (n=38746, m=807598) k=18491 color(s) 529.256 millisecond(s)
graphs/dac/6pipe.bliss (n=65839, m=1625050) k=31204 color(s) 1091.92 millisecond(s)
graphs/dac/7pipe.bliss (n=100668, m=2997942) k=47245 color(s) 2055.46 millisecond(s)
graphs/dac/Urq3_4.bliss (n=292, m=2416) k=54 color(s) 7.059 millisecond(s)
graphs/dac/Urq3_9.bliss (n=306, m=2578) k=53 color(s) 1.602 millisecond(s)
graphs/dac/fpga11_13.bliss (n=598, m=4576) k=3 color(s) 2.567 millisecond(s)
graphs/dac/fpga11_20.bliss (n=920, m=10120) k=3 color(s) 5.276 millisecond(s)
graphs/dac/fpga13_10.bliss (n=530, m=3740) k=11 color(s) 2.273 millisecond(s)
graphs/dac/fpga13_12.bliss (n=636, m=5112) k=11 color(s) 3.284 millisecond(s)
graphs/dac/hole11.bliss (n=276, m=1980) k=3 color(s) 1.224 millisecond(s)
graphs/dac/hole12.bliss (n=325, m=2496) k=3 color(s) 1.37 millisecond(s)
graphs/dac/pret150_25_ms.bliss (n=1504, m=7506) k=8 color(s) 4.484 millisecond(s)
graphs/dac/pret60_25_ms.bliss (n=1080, m=3640) k=5 color(s) 2.406 millisecond(s)
graphs/dac/s3-3-3-3.bliss (n=2558, m=23400) k=1194 color(s) 13.952 millisecond(s)
graphs/dac/s3-3-3-8.bliss (n=2432, m=21552) k=1200 color(s) 13.191 millisecond(s)
graphs/dac/s4-4-3-1.bliss (n=10354, m=89928) k=5642 color(s) 51.983 millisecond(s)
graphs/dac/s4-4-3-2.bliss (n=9974, m=84696) k=5639 color(s) 49.243 millisecond(s)
graphs/dac/s4-4-3-3.bliss (n=9970, m=84696) k=5631 color(s) 49.85 millisecond(s)
graphs/dac/s4-4-3-4.bliss (n=10714, m=95160) k=4509 color(s) 53.911 millisecond(s)
graphs/dac/s4-4-3-5.bliss (n=11072, m=100560) k=6083 color(s) 58.464 millisecond(s)
graphs/dac/s4-4-3-6.bliss (n=9620, m=79776) k=4974 color(s) 46.423 millisecond(s)
graphs/dac/s4-4-3-7.bliss (n=10362, m=89976) k=5879 color(s) 52.759 millisecond(s)
graphs/dac/s4-4-3-8.bliss (n=6608, m=44592) k=3347 color(s) 26.364 millisecond(s)
graphs/dac/s4-4-3-9.bliss (n=12920, m=129936) k=6298 color(s) 78.455 millisecond(s)
graphs/dac/x1_32.bliss (n=436, m=1680) k=156 color(s) 2.004 millisecond(s)
graphs/dac/x1_36.bliss (n=492, m=1896) k=176 color(s) 1.396 millisecond(s)
29 graph(s) processed in 4.88995 second(s)
```


References:

Berkholz, Bonsma, and Grohe. Tight Lower and Upper Bounds for the Complexity of Canonical Colour Refinement. 2015. 
[arXiv:1509.08251.](https://arxiv.org/abs/1509.08251)
