#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char * argv[]) {

    FILE *in, *out;
    int n, u ,v, i, sor, des;
    

    // Check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Get the order and make sure there is only one argument
    if( fscanf(in, "%d", &n) != 1) {
        printf("Error in first line of input %s\n", argv[1]);
        exit(1);
    }

    // Initialize Graph G of order n
    Graph G = newGraph(n);

    // Get first edge and make sure there are two arguments
    if(fscanf(in, "%d %d", &u, &v) != 2) {
        printf("Error in second line of input %s\n", argv[1]);
        exit(1);
    }

    // Set line counter equal to 2
    i = 2;

    // Run loop while the vertices inputted don't point to 0
    while(u!=0 && v!=0) {
        // Add edge to the Graph
        addEdge(G,u,v);
        // Increment line counter
        i++;
        // Get next edge and make sure there are two arguments
        if(fscanf(in, "%d %d", &u, &v) != 2) {
        printf("Error in line %d of input %s\n", i, argv[1]);
        exit(1);
        }
    }

    printGraph(out,G);

    // Incremenet line counter
    i++;

    // Get first path and make sure there are two arguments
    if(fscanf(in, "%d %d", &sor, &des) != 2) {
        printf("Error in line %d of input %s\n", i, argv[1]);
        exit(1);
    }

    // Create new List L
    List L = newList();

    // Run loop while the paths inputted don't point to 0
    while(sor!=0 && des!=0) {
        // Call BFS on source sor
        BFS(G,sor);

        // Get path from source to destination
        getPath(L,G,des);

        // Get distance from source to destination
        int dist = getDist(G,des);

        // If the distance is infinity, print out the messages accordingly
        if(dist == INF) {
            fprintf(out, "\nThe distance from %d to %d is infinity\n", sor, des);
            fprintf(out, "No %d-%d path exists", sor, des);

        // Else, print out the distance along with the shortest path
        } else {
            fprintf(out, "\nThe distance from %d to %d is %d\n", sor, des, dist);
            fprintf(out, "A shortest %d-%d path is: ", sor, des);
            printList(out,L);
        }
        fprintf(out, "\n");

        // Clear the List after every iteration
        clear(L);

        // Increment the line counter
        i++;

        // Get the next path and make sure there are two arguments
        if(fscanf(in, " %d %d", &sor, &des) != 2) {
            printf("Error in line %d of input %s\n", i, argv[1]);
            exit(1);
        }
    }

    // Free the List and Graph
    freeList(&L);
    freeGraph(&G);

    // Close the files and return
    fclose(in);
    fclose(out);
    return(0);

}

