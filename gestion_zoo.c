#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nomnre_max_animaux 100

int count_animaux_id = 0;

typedef struct
{
    int id;
    char nom[20];
    char espece[20];
    int age;
    char habitat[20];
    float poids;
} Animal;

// fonction pour vider le terminal .
void clear()
{
    system("cls");
}
// fonction pour pauser le terminal .
void pause()
{
    system("pause");
}

char *saisir_chaine_de_caractere(char text[], int size)
{
    char *input = malloc(size * sizeof(char));
    printf("%s", text);
    getchar();
    fgets(input, size, stdin);
    input[strlen(input) - 1] = '\0';
    return input;
}

Animal cree_un_animal()
{
    Animal animal;
    strcpy(animal.nom, saisir_chaine_de_caractere("Nom Animal :", 20));
    strcpy(animal.espece, saisir_chaine_de_caractere("Espece :", 20));
    strcpy(animal.habitat, saisir_chaine_de_caractere("Habitat :", 20));

    printf("Poids :");
    scanf("%f", &animal.poids);
    printf("Age :");
    scanf("%d", &animal.age);
    animal.id = count_animaux_id++;
    return animal;
}

void Ajouter_un_animal(Animal animal[])
{
    animal[count_animaux_id] = cree_un_animal();
    clear();
    printf("\nl'animal ajoute avec succes !\n ");
    pause();
    clear();
}

Animal fichier_to_tableau_animaux(Animal animal[])
{
    FILE *fichier;
    char ligne[200];
    fichier = fopen("animaux.csv", "r");
    if (fichier == NULL)
    {
        printf("erreur d'overteur fichier");
    }

    while (fgets(ligne, 200, fichier))
    {
        int mon_posion_dans_linge = 0;
        char *info_animal = strtok(ligne, ",");
        animal[count_animaux_id].id = count_animaux_id;
        while (info_animal != NULL)
        {
            switch (mon_posion_dans_linge)
            {
            case 1:
                strcpy(animal[count_animaux_id].nom, info_animal);
                break;
            case 2:
                strcpy(animal[count_animaux_id].espece, info_animal);
                break;
            case 3:
                animal[count_animaux_id].age = atoi(info_animal);
                break;
            case 4:
                strcpy(animal[count_animaux_id].habitat, info_animal);
                break;
            case 5:
                animal[count_animaux_id].poids = atof(info_animal);
                break;

            default:
                break;
            }
            mon_posion_dans_linge++;
            info_animal = strtok(NULL, ",");
        }
        count_animaux_id++;
    }
}

void Afficher_animal(Animal animal)
{
    printf("%-5d", animal.id);
    printf("|%-10s", animal.nom);
    printf("|%-10s", animal.espece);
    printf("|%-5d", animal.age);
    printf("|%-10s", animal.habitat);
    printf("|%-10.2f\n", animal.poids);
}

void Afficher_tous_les_animaux(Animal animal[], char message[])
{

    printf("%s", message);
    printf("------------------------------------------------------\n");
    printf("%-5s|%-10s|%-10s|%-5s|%-10s|%-10s\n", "ID", "NOM", "ESPECE", "AGE", "HABITIT", "POIDS");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < count_animaux_id; i++)
        Afficher_animal(animal[i]);
}

void trie_animaux_par_nom(Animal animal[])
{

    int changment = 1;

    while (changment)
    {
        changment = 0;
        for (int i = 0; i < count_animaux_id - 1; i++)
        {
            if (strcmp(animal[i].nom, animal[i + 1].nom) > 0)
            {
                Animal tmp = animal[i];
                animal[i] = animal[i + 1];
                animal[i + 1] = tmp;
                changment = 1;
            }
        }
    }
}

void trie_animaux_par_age(Animal animal[])
{

    int changment = 1;

    while (changment)
    {
        changment = 0;
        for (int i = 0; i < count_animaux_id - 1; i++)
        {
            if (animal[i].age > animal[i + 1].age)
            {
                Animal tmp = animal[i];
                animal[i] = animal[i + 1];
                animal[i + 1] = tmp;
                changment = 1;
            }
        }
    }
}

void Afficher_les_animaux_d_un_habitat_specefique(Animal animal[], char habitat[])
{
    int count = 0;
    printf("------------------------------------------------------\n");
    printf("%-5s|%-10s|%-10s|%-5s|%-10s|%-10s\n", "ID", "NOM", "ESPECE", "AGE", "HABITIT", "POIDS");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < count_animaux_id; i++)
        if (strcmp(animal[i].habitat, habitat) == 0)
        {
            Afficher_animal(animal[i]);
            count++;
        }
    if (count == 0)
        printf("\taucan animal d'un habitat %s  !\n", habitat);
}

void option_affichage(Animal animal[])
{

    int choix;

    do
    {
        printf("========= Gestion du Zoo ========\n");
        printf("=========Option Affichage=========\n");
        printf("1. Afficher la liste des animaux complet \n");
        printf("2. Trier par nom d'un animal\n");
        printf("3. Trier par age d'un animal\n");
        printf("4. Afficher les animaux d'un habitat specefique\n");
        printf("0. retour le menu Principale\n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            clear();
            Afficher_tous_les_animaux(animal, "");
            pause();
            break;

        case 2:
            clear();
            trie_animaux_par_nom(animal);
            Afficher_tous_les_animaux(animal, "----------les animaux trier par leurs noms---------\n");
            pause();
            break;
        case 3:
            clear();
            trie_animaux_par_age(animal);
            Afficher_tous_les_animaux(animal, "----------les animaux trier par leurs ages---------\n");
            pause();
            break;
        case 4:
            clear();
            Afficher_les_animaux_d_un_habitat_specefique(animal, saisir_chaine_de_caractere("entrer habitat", 20));
            pause();
            break;

        default:
            break;
        }

        clear();
    } while (choix != 0);
}

void menu_affichage_prancipale(Animal animal[])
{

    int choix;

    do
    {
        printf("========= Gestion du Zoo ========\n");
        printf("=========Menu Principale=========\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux\n");
        printf("3. Modifier un animal\n");
        printf("4. Supprimer un animal\n");
        printf("5. Rechercher un animal\n");
        printf("6. Statistiques\n");
        printf("0. Quitter\n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            clear();
            Ajouter_un_animal(animal);
            break;
        case 2:
            clear();
            option_affichage(animal);
            pause();
            break;

        default:
            break;
        }

        clear();
    } while (choix != 0);
}

void Modifier_un_animal(Animal animal[])
{
    int id;
    printf("entre id de animal");
    scanf("%d", &id);
    if (id >= 0 && id < count_animaux_id)
    {
        printf("\tvoici information d'animal id:%d\n", id);
        printf("------------------------------------------------------\n");
        printf("%-5s|%-10s|%-10s|%-5s|%-10s|%-10s\n", "ID", "NOM", "ESPECE", "AGE", "HABITIT", "POIDS");
        printf("------------------------------------------------------\n");
        Afficher_animal(animal[id]);
    }
    else
        printf("\tl'animal id:%d n'existe pas !\n", id);
}

int main()
{
    // menu_affichage_prancipale();
    Animal a[Nomnre_max_animaux];
    fichier_to_tableau_animaux(a);
    Modifier_un_animal(a);
    // menu_affichage_prancipale(a);
}