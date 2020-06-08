#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

typedef struct GraphObj {

    // Array of Lists whose ith element contains the neighbors of vertex i
    List* neighbor;
    // Array of ints whose ith element is the color (white,grey,black) of vertex i
    int* color;
    // Array of ints whose ith element is the parent of vertex i
    int* parent;
    // Array of ints whose ith element is the distance from 
    // the (most recent) source to vertex i
    int* distance;
    // The number of vertices of the graph
    int order;
    // The number of edges of the graph
    int size;
    // Vertex that was most recently used as source for BFS
    int source;

} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n) {

    // Allocate memory for the graph
    Graph G = malloc(sizeof(GraphObj));

    // Make sure there was memory allocated for the graph
    assert(G != NULL);

    // Allocate memory for the neighbor, color, parent, and distance arrays
    G->neighbor = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->distance = malloc((n+1) * sizeof(int));

    // Neighbor becomes an array of Lists, initialize the color 
    // array to 0 (white), initialize the parent array to NIL 
    // (undefined vertex) and the distance array to INF (infinity)
    for(int i=1; i<n+1; i++) {
        G->neighbor[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    // The order is n (number of vertices)
    // Initialize the size to 0 and source to NIL
    G->order = n;
    G->size = 0;
    G->source = NIL;

    return(G);

}

// Frees all dynamic memory associated with the Graph 
// *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {

    // Checks if pG or its pointer is NULL
    if(pG!=NULL && *pG!=NULL) {

        int n = getOrder(*pG);

        // Traverse through neighbor to free each List inside of it
        for(int i=1; i<n+1; i++) {
            freeList(&(*pG)->neighbor[i]);
        }

        // Free neighbor, color, parent, and distance arrays
        // Free the graph and set it equal to NULL
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;

    }

}

// Access functions -----------------------------------------------------------

// Returns the number of vertices in this graph
int getOrder(Graph G) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }

    return(G->order);
}

// Returns the number of edges in this graph
int getSize(Graph G) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }

    return(G->size);
}

// Returns the source vertex most recently used in function 
// BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(1);
    }

    return(G->source);
}

// Returns the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u) {

    // Check if this Graph is empty
    if(G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }

    int par;
    // Check if u is a valid vertex
    if(1<=u && u<=getOrder(G)) {
        par = G->parent[u];
    } else {
        printf("Graph Error: getParent() called on improper Graph");
        exit(1);
    }

    return par;
}

// Returns the distance from the most recent BFS source to 
// vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(1);
    }

    int dist;
    // Check if u is a valid vertex
    if(1<=u && u<=getOrder(G)) {
        dist = G->distance[u];
    } else {
        printf("Graph Error: getDist() called on improper Graph");
        exit(1);
    }

    return dist;
}

// Appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Note: BFS() must be called before getPath() because there needs to be a source vertex
void getPath(List L, Graph G, int u) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(1);
    }

    // The recursive function starts from the destination vertex and
    // tries to reach back to the source vertex.
    // Checks if BFS() was called and if u is a valid vertex.
    if(getSource(G)!=NIL && 1<=u && u<=getOrder(G)) {
        // If we have reached back to the source vertex, there
        // is a path, so first append the source vertex to the List.     
        if(u == getSource(G)) {
            append(L, getSource(G));
        // If the parent vertex of the path is NIL, reaching back to the
        // source isn't possible (there is no path) and append NIL to the List.
        } else if(G->parent[u] == NIL) {
            append(L, NIL);
        // Recursively call getPath() again to move closer back to the source.
        // Append the current vertex to the List to create the path.
        } else {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    } else {
        printf("Graph Error: getPath() called on improper Graph");
        exit(1);
    }

}

// Manipulation procedures ----------------------------------------------------

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(1);
    }
    
    int n = getOrder(G);
    
    // Call the clear function in List ADT for the neighbor array, initialize the 
    // color array back to 0, the parent array to NIL, and the distance array to INF.
    for(int i=1; i<n+1; i++) {
        clear(G->neighbor[i]);
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    // Initialize order to n, size to 0, and source to NIL
    G->order = n;
    G->size = 0;
    G->source = NIL;
}

// Inserts a new edge joining u to v, i.e. u is added to 
// the adjacency List of v, and v to the adjacency List of u. 
// Maintains list in sorted order by increasing labels.
void addEdge(Graph G, int u, int v) {

    // Check if the Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(1);
    }

    // Get the adjacency lists of vertices u and v
    List M = G->neighbor[u];
    List N = G->neighbor[v];

    // Check if u and v are valid vertices
    if(1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G)) {

        // Increment the number of edges by 1
        G->size = G->size + 1;

        // Add v to u's adjacency list first.
        // Just append v if the adjacency list for u is empty.
        if(length(M) == 0) {
            append(M, v);
        } else {
            // Start at the front of u's adjacency list
            moveFront(M);
            // Go through u's adjacency list to find 
            // the right spot to append v and maintain sorted order.
            while(place(M)>=0 && get(M)<v) {
                // Move the cursor
                moveNext(M);
            }
            // Insert before the cursor if we found the right spot
            // to append v and maintain sorted order.
            if(place(M) >= 0) {
                insertBefore(M, v);
            } else {
                // If we went through all of the adjacent vertices 
                // in u then just append v at the end of the list.
                append(M,v);
            }
        }

        // Add u to v's adjacency list now.
        // Just append u if the adjacency list for v is empty.
        if(length(N) == 0) {
            append(N, u);
        } else {
            // Start at the front of v's adjacency list
            moveFront(N);
            // Go through v's adjacency list to find 
            // the right spot to append u and maintain sorted order.
            while(place(N)>=0 && get(N)<u) {
                // Move the cursor
                moveNext(N);
            }
            // Insert before the cursor if we found the right spot
            // to append u and maintain sorted order.
            if(place(N) >= 0) {
                insertBefore(N, u);
            } else {
                // If we went through all of the adjacent vertices in 
                // v then just append u at the end of the list
                append(N,u);
            }
        }

    } else {
        printf("Graph Error: addEdge() called on improper Graph");
        exit(1);
    }
}

// Inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v) {

    // Check if the Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }

    // Get the adjacency list of u
    List M = G->neighbor[u];

    // Check if u and v are valid vertices
    if(1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G)) {

        // Increment the number of edges by 1
        G->size = G->size + 1;

        // Just append v if the adjacency list for u is empty
        if(length(M) == 0) {
            append(M, v);
        } else {
            // Start at the front of u's adjacency list
            moveFront(M);
            // Go through u's adjacency list to find 
            // the right spot to append v and maintain sorted order
            while(place(M)>=0 && get(M)<v) {
                // Move the cursor
                moveNext(M);
            }
            // Insert before the cursor if we found the right spot
            // to append v and maintain sorted order
            if(place(M) >= 0) {
                insertBefore(M, v);
            } else {
                // If we went through all of the adjacency vertices in u 
                // then just append v at the end of the list
                append(M,v);
            }
        }

    } else {
        printf("Graph Error: addArc() called on improper Graph");
        exit(1);
    }
}

// Runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {

    // Check if this Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }

    // Checks if s is a valid vertex
    if(s<1 || s>getOrder(G)) {
        printf("Graph Error: BFS() called on improper source");
        exit(1);
    }

    int n = getOrder(G);

    // Initialize all colors to white, all parents to NIL, and all distances to INF
    for(int i=1; i<n+1; i++) {
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    // Change the color of the source to gray because we've discovered
    // the vertex itself, but not its neighbors yet
    G->color[s] = 1;
    // Set the distance from the source to 0
    G->distance[s] = 0;
    // Set the parent of the source to NIL
    G->parent[s] = NIL;
    // Set the source accordingly
    G->source = s;

    // Initialize a List, which implements the FIFO queue, and append the source to it
    List Q = newList();
    append(Q, s);

    // Run the loop while the List isn't empty
    while(length(Q) != 0) {

        // Get the front vertex in the List
        int x = front(Q);

        // Delete the front vertex in the List
        deleteFront(Q);

        // Get the adjacency list of the front vertex in the List
        List Adj = G->neighbor[x];

        // Check if the adjacency list of the front
        // vertex in the List is empty
        if(length(Adj) != 0) {

            // Traverse through the adjacency list of the front vertex in the List
            for(moveFront(Adj); place(Adj)>=0; moveNext(Adj)) {

                // Get the vertex at the cursor of the adjacency list
                int y = get(Adj);

                // Check if the vertex is undiscovered
                if(G->color[y] == 0) {
                    // Change the color of the vertex to grey
                    G->color[y] = 1;

                    // Set the distance of the vertex to its parent's distance plus 1
                    G->distance[y] = G->distance[x] + 1;

                    // Set the parent of the vertex to the front vertex in the List
                    G->parent[y] = x;

                    // Add the vertex to the List
                    append(Q, y);
                }

            }

        }

        // Change the color of the front vertex in the List to black,
        // since all of its neighbors have been discovered.
        G->color[x] = 2;

    }

    // Free the List
    freeList(&Q);
}

// Other operations -----------------------------------------------------------

// Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {

    // Check if the Graph is NULL
    if(G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }

    int n = getOrder(G);

    // Prints out each vertex in the Graph along with its adjacency list
    for(int i=1; i<n+1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
        fprintf(out, "\n");
    }

}

