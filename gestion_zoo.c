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

void header_de_tableau()
{
    printf("------------------------------------------------------\n");
    printf("%-5s|%-10s|%-10s|%-5s|%-10s|%-10s\n", "ID", "NOM", "ESPECE", "AGE", "HABITIT", "POIDS");
    printf("------------------------------------------------------\n");
}
void footer_de_tableau()
{
    printf("------------------------------------------------------\n");
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
int saisir_entier(char text[], char message_errer[])
{
    int entier;
    printf("%s", text);

    while (scanf("%d", &entier) != 1)
    {
        clear();
        printf("%s", message_errer);
        while (getchar() != '\n')
            ;
    }
    return entier;
}

char saisir_caracter(char text[])
{
    char caracter;
    printf("%s", text);

    do
    {
        caracter = getchar();
    } while (caracter == '\n' || caracter == ' ');

    return caracter;
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
    header_de_tableau();
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
    header_de_tableau();
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
        printf("=========Options D'Affichage=========\n");
        printf("1. Afficher la liste des animaux complet \n");
        printf("2. Trier par nom d'un animal\n");
        printf("3. Trier par age d'un animal\n");
        printf("4. Afficher les animaux d'un habitat specefique\n");
        printf("0. retour le menu Principale\n");
        choix = saisir_entier("", "\terreur de saisir!\n");

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
        case 0:
            break;
        default:
            clear();
            printf("choix invalide !\n");
            pause();
            break;
        }

        clear();
    } while (choix != 0);
}

void Modifier_habitat_animal(Animal animal[], int id_modification)
{
    strcpy(animal[id_modification].habitat, saisir_chaine_de_caractere("nouvel habitat : ", 20));
}

void Modifier_age_animal(Animal animal[], int id_modification)
{
    animal[id_modification].age = saisir_entier("nouvel age :", " entree invalid[0-9] :");
}

void options_de_modifier(Animal animal[], int id_modification)
{
    int choix;
    do
    {
        printf("========= Gestion du Zoo ========\n");
        printf("=========Menu Modification=========\n");
        printf("1. Modifier l'habitat \n");
        printf("2. Modifier l'age\n");
        printf("0. Quitter\n");
        choix = saisir_entier("", "entree invalid [0-2] :");
        switch (choix)
        {
        case 1:
            clear();
            Modifier_habitat_animal(animal, id_modification);
            pause();
            choix = 0;
            break;
        case 2:
            clear();
            Modifier_age_animal(animal, id_modification);
            pause();
            choix = 0;
            break;

        default:
            clear();
            printf("choix invalide !\n");
            pause();
            break;
        }
        clear();
    } while (choix != 0);
}

void Modifier_un_animal(Animal animal[])
{
    int select_id_pour_modifier = saisir_entier("entrer ID: ", "entree invalide,ID [0-9] :");
    if (select_id_pour_modifier >= 0 && select_id_pour_modifier < count_animaux_id)
    {
        printf("\tvoici information d'animal id:%d\n", select_id_pour_modifier);
        header_de_tableau();
        Afficher_animal(animal[select_id_pour_modifier]);
        printf("------------------------------------------------------\n");
        options_de_modifier(animal, select_id_pour_modifier);
    }
    else
        printf("\tl'animal id:%d n'existe pas !\n", select_id_pour_modifier);
}
void Supprimer_un_animal(Animal animal[], int id_animal_supprimer)
{

    for (int i = id_animal_supprimer; i < count_animaux_id - 1; i++)
    {
        animal[i] = animal[i + 1];
        animal[i].id--;
    }
    count_animaux_id--;
}
void options_de_supprimer(Animal animal[])
{
    char choix;
    int id_select_pour_supprimer = saisir_entier("ID :", "entree invalid [0-9]: ");
    if (id_select_pour_supprimer >= 0 && id_select_pour_supprimer < count_animaux_id)
    {
        printf("\tvoici information d'animal id:%d\n", id_select_pour_supprimer);
        header_de_tableau();
        Afficher_animal(animal[id_select_pour_supprimer]);
        footer_de_tableau();

        do
        {
            choix = saisir_caracter("vieullez vous supprimer [y/n] :");
            switch (choix)
            {
            case 'y':
                clear();
                Supprimer_un_animal(animal, id_select_pour_supprimer);
                printf("l'animal de ID:%d  suprimer !\n", id_select_pour_supprimer);
                pause();
                choix = 'n';
                break;
            case 'n':
                break;
            default:
                clear();
                printf("choix invalide !\n");
                pause();
                break;
            }
            clear();
        } while (choix != 'n');
    }
    else
        printf("\taucan animal d ID :%d   !\n", id_select_pour_supprimer);
}

void Rechercher_par_id(Animal animal[])
{
    int id = saisir_entier("ID : ", "erreur de saisir [0-9] :");
    header_de_tableau();
    for (int i = 0; i < count_animaux_id; i++)
        if (animal[i].id == id)
        {
            Afficher_animal(animal[i]);
            return;
        }
    printf("ID:%d n'existe pas !\n", id);
}
void Rechercher_par_nom(Animal animal[])
{
    char *nom = saisir_chaine_de_caractere("Nom :", 20);
    int count = 0;
    header_de_tableau();
    for (int i = 0; i < count_animaux_id; i++)
        if (strcmp(animal[i].nom, nom) == 0)
        {
            Afficher_animal(animal[i]);
            count++;
        }
    if (count == 0)
        printf("\tNom:%s n'existe pas !\n", nom);
}
void Rechercher_par_espece(Animal animal[])
{
    char *espece = saisir_chaine_de_caractere("Espece :", 20);
    int count = 0;
    header_de_tableau();
    for (int i = 0; i < count_animaux_id; i++)
        if (strcmp(animal[i].espece, espece) == 0)
        {
            Afficher_animal(animal[i]);
            count++;
        }
    if (count == 0)
        printf("\tEspece:%s n'existe pas !\n", espece);
}
void options_Rechercher_un_animal(Animal animal[])
{
    int choix;

    do
    {
        printf("========= Gestion du Zoo ========\n");
        printf("=========Option Recherche=========\n");
        printf("1. Rechercher par id. \n");
        printf("2. Rechercher par nom.\n");
        printf("3. Rechercher par espèce\n");
        printf("0. retour le menu Principale\n");
        choix = saisir_entier("", "erreur de saisir!\n");

        switch (choix)
        {
        case 1:
            clear();
            Rechercher_par_id(animal);
            pause();
            break;

        case 2:
            clear();
            Rechercher_par_nom(animal);
            pause();
            break;
        case 3:
            clear();
            Rechercher_par_espece(animal);
            pause();
            break;
        case 0:
            break;

        default:
            clear();
            printf("choix invalide !\n");
            pause();
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
        choix = saisir_entier("", "\nerreur de saisir\n");

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
        case 3:
            clear();
            Modifier_un_animal(animal);
            pause();
            break;
        case 4:
            clear();
            options_de_supprimer(animal);
            pause();
            break;
        case 5:
            clear();
            options_Rechercher_un_animal(animal);
            pause();
            break;

        case 0:
            break;

        default:
            clear();
            printf("choix invalide !\n");
            pause();
            break;
        }

        clear();
    } while (choix != 0);
}

int main()
{
    // menu_affichage_prancipale();
    Animal a[Nomnre_max_animaux];
    fichier_to_tableau_animaux(a);
    menu_affichage_prancipale(a);
}