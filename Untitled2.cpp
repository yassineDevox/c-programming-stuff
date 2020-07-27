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
int numberOfEdgesNotNull = 0;

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
        printf(" \n10 : Quitter le programme\n\t\tVotre choix : ");
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
    for (int i = 0; i < numberOfNodes-2; i++)
    {
        for (int j = i+1; j < numberOfNodes; j++)
        {
            if (GRAPH_MAT[i][j] != 0){
        		printf("\t+ ( %c )--[ %3d ] <--> ( %c )\n", vertex[i], GRAPH_MAT[i][j], vertex[j]);
				numberOfEdgesNotNull++; 
			}
        }
        printf("\t\t-------------\n\n");
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
        for (int j = i+1; j < numberOfNodes; j++)
        {
            do
            {
                printf("\n Node( %c ) <--> node( %c ) : ", vertex[i], vertex[j]);
                scanf("%d", &GRAPH_MAT[i][j]);

            } while (GRAPH_MAT[i][j] < 0);
            GRAPH_MAT[i][j]=GRAPH_MAT[i][j];
        }
    }
}

void saisirConstraintsForNodes()
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

    for (int i = 0; i < numberOfNodesDamaged; i++)
    {
        do
        {
            printf(" \nEnter node index (between 0 & %d ) : ", numberOfNodes - 1);
            scanf("%d", &damagedNodes[i]);

        } while (damagedNodes[i] < 0 || (numberOfNodes - 1) < damagedNodes[i]);
    }
}

void afficherContraintsForNodes()
{
    printf("\nLes renpoints non-fonctionnel :\n ");

    for (int i = 0; i < numberOfNodesDamaged - 1; i++)
    {
    	int ii=damagedNodes[i];
        printf("(%c) , ", vertex[ii]);
    }
    int ii=damagedNodes[numberOfNodesDamaged - 1];
    printf("(%c)", vertex[ii]);
}

void saisirConstraintForEdges()
{

    //delete all previous values of edges-constraints
    numberOfEdgesDamaged = 0;
    free(damagedNodes);


    //enter the number of nodes non fonctionnel
    do
    {
        printf("\nHow much Edges are damaged ? ( < %d) : ", numberOfEdgesNotNull);
        scanf("%d", &numberOfEdgesDamaged);

    } while (numberOfEdgesDamaged > numberOfEdgesNotNull);

    // create a dynamic array to store the indexs of damaged nodes

    damagedEdges = (int **)malloc(numberOfEdgesDamaged * sizeof(int *));

    for (int i = 0; i < numberOfEdgesDamaged; i++)
        damagedEdges[i] = (int *)malloc(2 * sizeof(int));

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

        } while (from >= numberOfNodes || to >= numberOfNodes);

        //store constraints values
        damagedEdges[i][0] = from;
        damagedEdges[i][1] = to;
    }
}

void afficherContraintsForEdges()
{

    printf("\nLes renpoints non-fonctionnel :\n ");

    for (int i = 0; i < numberOfEdgesDamaged; i++)
    {
        int from = damagedEdges[i][0];
        int to = damagedEdges[i][1];
        printf("\n[ %c ]-->[ %c ] ",vertex[from],vertex[to]);
    }
}




void saisirDurrationsForHeureDePointConstraints()
{   
    durrationsForHeuresDepoints = (int *) malloc(sizeof(int) * numberOfEdgesNotNull);

    printf("\nSaisir les durrés a ajouter dans le cas d'heure de points :\n");
    for (int i = 0, k = 0; i < numberOfNodes-2; i++)
    {
        for (int j = i+1; j < numberOfNodes; j++)
        {
            if(GRAPH_MAT[i][j]!=0){
                
                printf("\n Node( %c ) <--> node( %c ) : ", vertex[i], vertex[j]);
                scanf("%d", &durrationsForHeuresDepoints[k]);
                k++;
            }
            
        }
    }
}

void afficherLesDurresHeurePoints()
{

    printf("\nLes durres d'heures de points : \n");
    
    for (int i = 0, k = 0; i < numberOfNodes-2; i++)
    {
        for (int j = i+1; j < numberOfNodes; j++)
        {
            if(GRAPH_MAT[i][j]!=0){
                
                printf("\n Node( %c ) <--> node( %c ) : %d mins", vertex[i], vertex[j],durrationsForHeuresDepoints[k]);
                k++;
            }
            
        }
    }
}


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
        afficherMatriceRoutes();

        goto continuer;
    }
    break;
    case 1:
    {
        saisirGraphe();
        afficherMatriceRoutes();

        goto continuer;
    }
    break;
    case 2:
    {
        saisirConstraintsForNodes();
        afficherContraintsForNodes();

        goto continuer;
    }
    break;
    case 3:
    {
        saisirConstraintForEdges();
        afficherContraintsForEdges();   
        goto continuer;
    }
    break;
    case 4:
    {
        saisirDurrationsForHeureDePointConstraints();
        afficherLesDurresHeurePoints();
        goto continuer;
    }
    break;
    case 5:
    {
        
        goto continuer;
    }
    break;
    case 6:
    {
        afficherContraintsForNodes();
        goto continuer;
    }
    break;
    case 7:
    {
        afficherContraintsForEdges();   
        goto continuer;
    }
    break;
    case 8:
    {
        afficherLesDurresHeurePoints();
        goto continuer;
    }
    break;
    case 9:
    {
        
        goto continuer;
    }
    break;
    default:
        
        goto fin;
        break;
    }

    continuer:
    int choix;
    printf("\n\nVous les vous continuer\nOui : 1\nNon:0\n\tVotre Choix : ");
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
