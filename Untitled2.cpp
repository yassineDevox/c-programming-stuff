#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999
#define MAX 10

// ower global graph matrix
int GRAPH_MAT[MAX][MAX];
int numberOfNodes;
int *damagedNodes;
int *addedDurationsInCaseOfPeakH;
int **damagedEdges;
int numberOfNodesDamaged = 0;
int numberOfEdgesDamaged = 0;
int numberOfEdgesExistant = 0;

char vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

//-----------------------functions------------

//tools
void vertexAndMat();

// extension
int menu();

void initialValues();

void displayMatrixOfRoutes();

void setGraphOfRoutes();

void setConstraintsForNodes();

void displayConstraintsForNodes();

void setConstraintsForEdges();

void displayConstraintsForEdges();

void setAddedDurationInCaseOfPeakH();

void displayAddedDurationInCaseOfPeakH();

void preTraitement();

int main()
{

menu:
    system("cls");
    //menu function

    int choice = menu();

    switch (choice)
    {
    case 0:
    {
        initialValues();
        goto continuer;
    }
    break;
    case 1:
    {
        setGraphOfRoutes();
        goto continuer;
    }
    break;
    case 2:
    {
        setConstraintsForNodes();
        goto continuer;
    }
    break;
    case 3:
    {
        setConstraintsForEdges();
        goto continuer;
    }
    break;
    case 4:
    {
        setAddedDurationInCaseOfPeakH();
        displayAddedDurationInCaseOfPeakH();
        goto continuer;
    }
    break;
    case 5:
    {
        displayMatrixOfRoutes();
        goto continuer;
    }
    break;
    case 6:
    {
        displayConstraintsForNodes();
        goto continuer;
    }
    break;
    case 7:
    {
        displayConstraintsForEdges();
        goto continuer;
    }
    break;
    case 8:
    {
        displayAddedDurationInCaseOfPeakH();
        goto continuer;
    }
    break;
    case 9:
    {
        preTraitement();
        goto continuer;
    }
    break;
    default:

        goto fin;
        break;
    }

continuer:
    int choix;
    printf("\n\nVoulez vous continuer\nOui : 1\nNon : 0\n\tVotre Choix : ");
    scanf("%d", &choix);

    if (choix == 1)
    {
        goto menu;
    }
    else
    {
        goto fin;
    }

fin:
    system("cls");
    printf("\nVous avez quitter le programme !!");
}

//-----------------------functions------------

//tools
void vertexAndMat()
{

    for (int i = 0; i < numberOfNodes; i++)
    {
        printf("%d  ", i);
    }
    printf("\n");

    for (int i = 0; i < numberOfNodes; i++)
    {
        printf("%c  ", vertex[i]);
    }
    printf("\n\n\n");
}
// extension
int menu()
{
    int choix;
    do
    {
        printf(" \nTrouver le petit chemin possible pour votre route \1 !!");
        printf(" \nMenu du Programme : !!");
        printf(" \n0 : Utiliser les valeurs initial ? ");
        printf(" \n1 : Remplire la matrice des boulevards");
        printf(" \n2 : Indiquer des ronds-points non fonctionnels");
        printf(" \n3 : Indiquer des boulevards non fonctionnels");
        printf(" \n4 : Remplir les durrees d'attentes en cas d'heure de pointe");
        printf(" \n5 : Afficher la matrice des boulevards ");
        printf(" \n6 : Afficher les ronds-points non fonctionnels");
        printf(" \n7 : Afficher les boulevards bloques");
        printf(" \n8 : Afficher les durees d'heures de pointes");
        printf(" \n9 : Afficher le chemin le plus court");
        printf(" \n10 : Quitter le programme\n\t\tVotre choix : ");
        scanf("%d", &choix);
    } while (choix < 0 || choix > 10);

    return choix;
}

void initialValues()
{
    int i, j, u, v;
    FILE *fp;
    char name[12] = "gMatrix.txt";
    fp = fopen(name, "r");
    fscanf(fp, "%d", &numberOfNodes);
    for (i = 0; i < numberOfNodes; i++)
        for (j = 0; j < numberOfNodes; j++)
            fscanf(fp, "%d", &GRAPH_MAT[i][j]);

    fclose(fp);
}

void displayMatrixOfRoutes()
{
    printf("\nGraphe des boulevards : \n\n\n");
    for (int i = 0; i < numberOfNodes - 1; i++)
    {
        for (int j = i + 1; j < numberOfNodes; j++)
        {
            if (GRAPH_MAT[i][j] != 0)
            {
                printf("\t+ ( %c )<--[ %3d ]--> ( %c )\n", vertex[i], GRAPH_MAT[i][j], vertex[j]);
                numberOfEdgesExistant++;
            }
        }
        printf("\t\t-------------\n\n");
    }
}

void setGraphOfRoutes()
{
    //enter values of the matrix by the user

    do
    {
        printf(" Entrer le nombre de noeuds constituant la graphe :  (> 0) : ");
        scanf("%d", &numberOfNodes);
    } while (numberOfNodes <= 0);

    //full the matrix by the values of edges for each node
    for (int i = 0; i < numberOfNodes - 1; i++)
    {
        for (int j = i + 1; j < numberOfNodes; j++)
        {
            do
            {
                printf("\n Node( %c ) <--> node( %c ) : ", vertex[i], vertex[j]);
                scanf("%d", &GRAPH_MAT[i][j]);

            } while (GRAPH_MAT[i][j] < 0);

            GRAPH_MAT[j][i] = GRAPH_MAT[i][j];
        }
    }
}

void setConstraintsForNodes()
{

    //delete all previous values of nodes-constraints
    numberOfNodesDamaged = 0;
    free(damagedNodes);

    //enter the number of nodes non fonctionnel
    do
    {
        printf("\nEntrer le nombre des noeuds non fonctionnel  ( < %d) : ", numberOfNodes);
        scanf("%d", &numberOfNodesDamaged);

    } while (numberOfNodesDamaged > numberOfNodes);

    // create a dynamic array to store the indexs of damaged nodes

    damagedNodes = (int *)malloc(sizeof(int) * numberOfNodesDamaged);

    printf("\n-------------- Rappel :\n");
    vertexAndMat();

    if (numberOfEdgesDamaged != 0)
        displayConstraintsForEdges();

    for (int i = 0; i < numberOfNodesDamaged; i++)
    {
        do
        {
            printf(" \nEnter node index (between 0 & %d ) : ", numberOfNodes - 1);
            scanf("%d", &damagedNodes[i]);

        } while (damagedNodes[i] < 0 || (numberOfNodes - 1) < damagedNodes[i]);
    }
}

void displayConstraintsForNodes()
{
    printf("\nLes ronds-points bloques :\n ");

    for (int i = 0; i < numberOfNodesDamaged - 1; i++)
    {
        int ii = damagedNodes[i];
        printf("(%c) , ", vertex[ii]);
    }
    int ii = damagedNodes[numberOfNodesDamaged - 1];
    printf("(%c)", vertex[ii]);
}

void setConstraintsForEdges()
{

    //delete all previous values of edges-constraints
    if (numberOfEdgesDamaged != 0)
    {
        numberOfEdgesDamaged = 0;
        free(damagedNodes);
    }

    //enter the number of nodes non fonctionnel
    do
    {
        printf("\nEntrer le nombre de boulevards bloques  ( < %d) : ", numberOfEdgesExistant + 1);
        scanf("%d", &numberOfEdgesDamaged);

    } while (numberOfEdgesDamaged > numberOfEdgesExistant);

    // create a dynamic array to store the indexes of damaged nodes

    damagedEdges = (int **)malloc(numberOfEdgesDamaged * sizeof(int *));

    for (int i = 0; i < numberOfEdgesDamaged; i++)
        damagedEdges[i] = (int *)malloc(2 * sizeof(int));

    printf("\n-------------- Rappel :\n");
    vertexAndMat();

    if (numberOfNodesDamaged != 0)
        displayConstraintsForNodes();


    int c1, c2;

    for (int i = 0; i < numberOfEdgesDamaged; i++)
    {
        int from = 0, to = 0;
        //Enter i to j values
        do
        {

            printf("\nFrom ( < %d) : ", numberOfNodes);
            scanf("%d", &from);
            printf("\tTo ( < %d) : ", numberOfNodes);
            scanf("%d", &to);

            c1 = from >= numberOfNodes || to >= numberOfNodes;
            c2 = GRAPH_MAT[from][to] == 0;

            if (c1)
            {
                printf("\nValeurs non correspondantes");
            }
            if (c2)
            {
                printf("\nPas de liaison entre les deux ronds-points");
            }
        } while (c1 || c2);

        //store constraints values
        damagedEdges[i][0] = from;
        damagedEdges[i][1] = to;
    }
}

void displayConstraintsForEdges()
{

    printf("\nLes boulevards bloques :\n ");

    for (int i = 0; i < numberOfEdgesDamaged; i++)
    {
        int from = damagedEdges[i][0];
        int to = damagedEdges[i][1];
        printf("\n[ %c ]-->[ %c ] ", vertex[from], vertex[to]);
    }
}

void setAddedDurationInCaseOfPeakH()
{
    addedDurationsInCaseOfPeakH = (int *)malloc(sizeof(int) * numberOfEdgesExistant);

    printf("\nSaisir les durees a ajouter dans le cas d'heure de pointes (En minutes):\n");
    for (int i = 0, k = 0; i < numberOfNodes - 1; i++)
    {
        for (int j = i + 1; j < numberOfNodes; j++)
        {
            if (GRAPH_MAT[i][j] != 0)
            {

                printf("\n rond-point( %c ) <--> rond-point( %c ) : ", vertex[i], vertex[j]);
                scanf("%d", &addedDurationsInCaseOfPeakH[k]);
                k++;
            }
        }
    }
}

void displayAddedDurationInCaseOfPeakH()
{

    printf("\nLes durees d'heures de pointes : \n");

    for (int i = 0, k = 0; i < numberOfNodes - 1; i++)
    {
        for (int j = i + 1; j < numberOfNodes; j++)
        {
            if (GRAPH_MAT[i][j] != 0)
            {
                printf("\n rond-point( %c ) <--> rond-point( %c ) : %d min", vertex[i], vertex[j], addedDurationsInCaseOfPeakH[k]);
                k++;
            }
        }
    }
}

void dijkstra(int G[MAX][MAX], int n, int u, int v)
{

    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], mindistance, nextnode, i, j;
    char vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int startnode = u;
    int endnode = v;
    int count = 1, k = 0, N, M, L;
    char *p = (char *)malloc(sizeof(char) + 1);

    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];

    //initialize pred[],distance[] and visited[]
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1;

    count = 1;

    while (count < n - 1)
    {
        mindistance = INFINITY;

        //nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        //check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    //print the path and distance of each node
    //for(i=0;i<n;i++)

    //print the path and distance of J node
    i = v;

    if (i != startnode)
    {
        printf("\nDistance to vertex  %c =  %d", vertex[i], distance[i]);
        //printf("\nPath= %c",vertex[i]);

        j = i;

        do
        {
            j = pred[j];
            //printf("<-%c",vertex[j]);
            *(p + k) = vertex[j];
            k++;
        } while (j != startnode);
    }

    printf("\nShortest path: ");

    N = k - 1;
    while (N + 1)
    {
        printf("%c -> ", *(p + N));
        N--;
    }
    printf("%c\n", vertex[i]);

    free(p);
}

void displayMat()
{
    for (int i = 0; i < numberOfNodes; i++)
    {

        for (int j = 0; j < numberOfNodes; j++)
        {

            if (GRAPH_MAT[i][j] == 0)
                printf(" - ");
            else
                printf(" %3d ", GRAPH_MAT[i][j]);
        }
        printf("\n");
    }
}

void preTraitement()
{
    //------------------applay changes to the graph

    // printf("\n\n________________________BEFORE_____________________\nn");
    // displayMat();

    for (int i = 0; i < numberOfNodesDamaged; i++)
    {
        int node_index = damagedNodes[i];
        printf(" %d ", node_index);
        for (int j = 0; j < numberOfNodes; j++)
            GRAPH_MAT[node_index][j] = 0;
    }

    for (int i = 0; i < numberOfEdgesDamaged; i++)
    {
        int from = damagedEdges[i][0];
        int to = damagedEdges[i][1];
        GRAPH_MAT[from][to] = GRAPH_MAT[to][from] = -1;
    }

    // printf("\n\n________________________AFTER_____________________\n\n");
    // displayMat();
    int u, v;
    printf("\nEnter the starting vertex:");
    scanf("%d", &u);
    printf("\nEnter the destination vertex:");
    scanf("%d", &v);
    dijkstra(GRAPH_MAT, numberOfNodes, u, v);
}
