#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ** randomize_adjacency(int n_rewires, int n_nodes, int n_edges, int (**adj), int *n_a, int *n_b, int seed)  {

    // Set seed
    srand(seed);

    int n = 0;

    while(n<n_rewires) {
        int i = rand()%n_edges; // Edge one
        int j = rand()%n_edges; // Edge two

        /* [> Check if the edges are different <] */
        if(i==j) {
            continue;
        } else {

            /* [> Nodes from edge i <] */
            int a = n_a[i];
            int b = n_b[i];
            /* [> Nodes from edge j <] */
            int c = n_a[j];
            int d = n_b[j];

            /* [> Check if the edges already exist <] */
            /* [> Check if auto-loops are being created <] */
            if(adj[a][d] == 0 && adj[c][b] == 0 && a!=d && a!=c && c!=b && b!=d) {
                /* [> Overwriting edges <] */
                n_b[i] = d;
                n_a[j] = b;
                n_b[j] = c;
                /* [> Overwriting adjacency matrix <] */
                adj[a][b] = 0;
                adj[b][a] = 0;

                adj[c][d] = 0;
                adj[d][c] = 0;

                adj[a][d] = 1;
                adj[d][a] = 1;

                adj[c][b] = 1;
                adj[b][c] = 1;
                n++;
                printf("%d", n);
            }
            else {
                continue;
            }
        }
    }
    return adj;
}
