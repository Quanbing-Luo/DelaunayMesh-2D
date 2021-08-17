# DelaunayMesh-2D
 This repository includes the source codes and manuscript for the paper: 
-  **Quanbing Luo**, Automatic Delaunay mesh generation method and physically-based mesh optimization method on two-dimensional regions, [Engineering with Computers](https://doi.org/10.1007/s00366-020-01262-x), 2021 (Published Online)

The source codes were divided to two parts: (1) Delaunay mesh generation method and (2) Physically-based mesh optimization. 

## Delaunay mesh generation method

Delaunay mesh generation method was divided to three  parts: (1) Geometry, (2) InitialMesh and (3) Mesh. In order to obtaining Delaunay mesh, the three parts must be run in order. The data generated the Geometry are needed by InitialMesh program and the data generated the InitialMesh are needed by the Mesh program. 


## Physically-based mesh optimization

Physically-based mesh optimization was divided to two  parts: (1) OptimizedNodes and (2) OptimizedMesh. In order to obtaining optimized mesh, the two parts must be run in order. The data generated the Mesh in previous subsection are needed by OptimizedNodes program and the data generated the OptimizedNodes are needed by the OptimizedMesh program. 


**Notice:** The source codes do not provide the intermediate mesh data and final mesh data. You should generate these data from Geometry step by step. Four different geometries are provided in the directory of Geometry. The is a Figure.m program in each program directory draw the figure of generated data.    


