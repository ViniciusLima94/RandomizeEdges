#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* For weighed networks, you need to preserve strengths not just degrees, so: */
/* Take a random pair of links ij and kl */
/* Consider the strengths w_ij, w_kl as well as w_il and w_kj */
/* Set w_il to a new value equal to old w_ij and w_ij to a new value equal to old w_il */
/* Set w_kj to a new value equal to old w_kl and w_kl to a new value equal to old w_kj */
/* Do the same for the pair ji and lk, since the coherence networks must be symmetric */

float **allocate_2D_array(int rows, int columns) {
    int k = 0;
    float **array = malloc(rows * sizeof (float *) );

    array[0] = malloc(columns * rows * sizeof (float) );
    for (k=1; k < rows; k++) {
        array[k] = array[0] + columns*k;
        /* bzero(array[k], columns * sizeof (float) ); */
    }

    /* bzero(array[0], columns * sizeof (float) ); */

    return array;
}

int has_duplicate(int i,int j,int k,int l) {
    if(i==j || i==k || i==l) {
        return 1;
    }
    else if(j==k || j==l) {
        return 1;
    }
    else if(k==l) {
        return 1;
    }
    else {
        return 0;
    }
}

float **copy_array(int rows, int columns, float **(matrix)) {

    /* Allocate copy of the matrix */
    float **matrix_cp = allocate_2D_array(rows,columns);

    /* Copying values to copy */
    for(int r=0;r<rows;r++) {
        for(int c=0;c<columns;c++) {
            matrix_cp[r][c] = matrix[r][c];
        }
    }

    return matrix_cp;
}

float ** randomize_adjacency_wei(int n_rewires, int n_nodes, float (**adj), int seed)  {

    // Set seed
    srand(seed);

    /* Create a copy of the adjacency  */
    float **Arnd = copy_array(n_nodes,n_nodes,adj);

    int n = 0;

    while(n<n_rewires) {

        /* if(verbose==1) { */
        /*     printf("%d \n", n); */
        /* } */

        int i = rand()%n_nodes; // Edge one
        int j = rand()%n_nodes; // Edge two
        int k = rand()%n_nodes; // Edge three
        int l = rand()%n_nodes; // Edge four

        if( has_duplicate(i,j,k,l) ) {
            continue;
        }
        else {

            /* Store old values */
            float w_ij  = Arnd[i][j];
            float w_kl  = Arnd[k][l];
            float w_il  = Arnd[i][l];
            float w_kj  = Arnd[k][j];

            /* Swap 1  */
            Arnd[i][l] = w_ij;
            Arnd[l][i] = w_ij;
            /* Swap 2  */
            Arnd[i][j] = w_kl;
            Arnd[j][i] = w_kl;
            /* Swap 3  */
            Arnd[k][j] = w_il;
            Arnd[j][k] = w_il;
            /* Swap 4  */
            Arnd[l][k] = w_kj;
            Arnd[k][l] = w_kj;

            n++;
        }
    }

    return Arnd;
}

void print_2D_array(int rows, int columns, float (**a)) {

    for(int r=0;r<rows;r++) {
        for(int c=0;c<columns;c++) {
            printf("%d", (int)a[r][c]);
        }
        printf("\n");
    }
    printf("\n");

}

/* Method to read matrix. */
float readmatrix(size_t rows, size_t cols, float (**a), const char* filename) {

    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%f", a[i] + j);
    }


    fclose (pf);
    return 1;
}

/* In case it is executed as main it will run a small example. */
int main(void) {
    // Number of nodes
    int n_nodes   = 49;
    // Number of edges 
    int n_edges   = 1176;
    // Number of rewires that will be applied
    /* int n_rewires = 100; */
    // Reading matrix from file
    /* int A[n_nodes][n_nodes]; */
    float **A     = allocate_2D_array(n_nodes, n_nodes);

    readmatrix(n_nodes, n_nodes,A,"adj.txt");
    print_2D_array(n_nodes,n_nodes,A);

    float **Acp  = copy_array(n_nodes,n_nodes,A);
    /* print_2D_array(n_nodes,n_nodes,Acp); */


    system("clear");
    for(int n_rewires=0; n_rewires<100; n_rewires++) {
        printf("it = %d\n", n_rewires);
        float **Arnd = randomize_adjacency_wei(n_rewires,n_nodes,A,0);
        print_2D_array(n_nodes,n_nodes,Arnd);
        sleep(1);
        system("clear");
    }
    /* float **Arnd = randomize_adjacency_wei(100,n_nodes,A,0,1); */
    /* print_2D_array(n_nodes,n_nodes,Arnd); */

    /* printf("%d\n", has_duplicate(1,1,2,3)); */
    /* printf("%d\n", has_duplicate(1,4,2,3)); */

    return 1;
}
