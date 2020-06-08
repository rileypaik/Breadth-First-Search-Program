#include "List.h"
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include <stdio.h>
#include <stdlib.h>

#define INF -1
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n);

// Frees all dynamic memory associated with the Graph 
// *pG,then sets thehandle *pG to NULL.
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

// Returns the number of vertices in this graph
int getOrder(Graph G);

// Returns the number of edges in this graph
int getSize(Graph G);

// Returns the source vertex most recently used in function 
// BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G);

// Returns the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u);

// Returns the distance from the most recent BFS source to 
// vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u);

// Appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Note: BFS() must be called before getPath() because there needs to be a source vertex
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// Inserts a new edge joining u to v, i.e. u is added to 
// the adjacency List of v, and v to the adjacency List of u. 
// Maintains list in sorted order by increasing labels.
void addEdge(Graph G, int u, int v);

// Inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v);

// Runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);

// Other operations -----------------------------------------------------------

// Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif

