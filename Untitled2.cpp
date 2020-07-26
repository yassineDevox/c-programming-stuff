#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999
#define MAX 10

// ower global graph matrix
int GRAPH_MAT[MAX][MAX];
int numberOfNodes;
int *damagedNodes;
int *durrationsForHeuresDepoints;
int **damagedEdges;
int numberOfNodesDamaged = 0;
int numberOfEdgesDamaged = 0;

char vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

//-----------------------functions------------

// extension
int menu()
{
    int choix;
    do
    {

        printf(" \nTrouver le petit chemin possible pour votre route \1 !!");
        printf(" \nMenu du Programme : !!");

        printf(" \n0 : Utiliser les valeurs initial ? ");
        printf(" \n1 : Remplire la matrice des routes");
        printf(" \n2 : Indiquer des rempoints non fonctionnel");
        printf(" \n3 : Indiquer des routes non fonctionnel");
        printf(" \n4 : Remplir les durr�es d'attents en cas d'heure de point ");
        printf(" \n5 : Afficher la matrice des routes ");
        printf(" \n6 : Afficher les rempoints non-fonctionnel");
        printf(" \n7 : Afficher les routes non-fonctionnel");
        printf(" \n8 : Afficher les durees d'heures de points ");
        printf(" \n9 : Afficher le chemin le plus court");
        printf(" \n10 : Quitter le programme\n\t\tvotre choix : ");
        scanf("%d", &choix);
        system("cls");
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

void afficherMatriceRoutes()
{
    printf("\nMatrice de routes : \n\n\n");
    for (int i = 0; i < numberOfNodes; i++)
    {
        for (int j = 0; j < numberOfNodes; j++)
        {
            if (GRAPH_MAT[i][j] != 0)
            printf("\t+ ( %c )--[ %3d ] --> ( %c )\n",vertex[i], GRAPH_MAT[i][j],vertex[j]);
        }
        printf("\t\t------------\n\n");
        
    }
}

void saisirGraphe()
{
    //enter values of the matrix by the user

    do
    {
        printf(" Entrer le nombre de noeuds constituant la graphe :  (> 0) : ");
        scanf("%d", &numberOfNodes);
    } while (numberOfNodes <= 0);

    //full the matrix by the values of edges for each node
    for (int i = 0; i < numberOfNodes; i++)
    {
        for (int j = 0; j < numberOfNodes; j++)
        {
            if (i != j)
                do
                {
                    printf("\n Node( %c ) --> node( %c ) : ", vertex[i], vertex[j]);
                    scanf("%d", &GRAPH_MAT[i][j]);

                } while (GRAPH_MAT[i][j] < 0);
        }
    }
}

void saisirConstraintsForNodes()
{

    numberOfNodesDamaged = 0;
    //enter the number of nodes non fonctionnel
    do
    {
        printf("\nEntrer le nombre des noeuds non fonctionnel  ( < %d) : ", numberOfNodes);
        scanf("%d", &numberOfNodesDamaged);

    } while (numberOfNodesDamaged > numberOfNodes);

    // create a dynamic array to store the indexs of damaged nodes

    damagedNodes = (int *)malloc(sizeof(int) * numberOfNodesDamaged);

    for (int i = 0; i < numberOfNodesDamaged; i++)
    {
        do
        {
            printf(" \nEnter node index (between 0 & %d ) : ", numberOfNodes - 1);
            scanf("%d", &damagedNodes[i]);

        } while ( damagedNodes[i] < 0 || (numberOfNodes - 1) < damagedNodes[i]);
    }
}

void afficherContraintsForNodes()
{
    printf("\nLes renpoints non-fonctionnel :\n ");

    for (int i = 0; i < numberOfNodesDamaged-1; i++)
    {
        printf("(%c) , ", vertex[damagedNodes[i]]);
    }
        printf("(%c)", vertex[damagedNodes[numberOfNodesDamaged-1]]);

}

int main()
{

    //menu function
    menu: int choice = menu();

    switch (choice)
    {
    case 0:
    {
        initialValues();
        afficherMatriceRoutes();
        
        getchar();
        goto menu;
    }
    break;
    case 1:
    {
        saisirGraphe();
        afficherMatriceRoutes();

        getchar();
        goto menu;
    }
    break;
    case 2:
    {
        saisirConstraintsForNodes();
        afficherContraintsForNodes();

        getchar();
        goto menu;
    }
    break;
    case 3:
    {
    }
    break;
    case 4:
    {
    }
    break;
    case 5:
    {
    }
    break;
    case 6:
    {
        afficherContraintsForNodes();
    }
    break;
    case 7:
    {
    }
    break;
    case 8:
    {
    }
    break;
    case 9:
    {
    }
    break;
    default:

        break;
    }
}
