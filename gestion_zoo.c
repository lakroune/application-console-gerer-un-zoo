#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Nomnre_max_animaux 100

int COUNT_ANIMAL = 0;
int ID_ANIMAL_AUTO_INCREMENT = 0;

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
    printf("|======================================================================|\n");
    printf("|%-5s|%-15s|%-15s|%-5s|%-15s|%-10s|\n", "ID", "NOM", "ESPECE", "AGE", "HABITAT", "POIDS");
    printf("|======================================================================|\n");
}
void footer_de_tableau()
{
    printf("|______________________________________________________________________|\n");
}

char *saisir_chaine_de_caractere(char text[], int size)
{
    char *input = malloc(size * sizeof(char));

    do
    {
        clear();
        printf("%s", text);
        fgets(input, size, stdin);
        input[strlen(input) - 1] = '\0';
    } while (strlen(input) == 0);
    return input;
}

int saisir_entier_positif(char text[], char message_errer[], int max)
{

    int entier, i;
    printf("%s", text);
    while (scanf("%d", &entier) != 1 || entier < 0 || entier > max)
    {
        clear();
        printf("%s", message_errer);
        while ((i = getchar()) != '\n' && i != EOF)
            ;
    }
    return entier;
}

float saisir_reel(char text[], char message_errer[])
{
    float reel;
    int i;
    printf("%s", text);

    while (scanf("%f", &reel) != 1 || reel < 0)
    {
        clear();
        printf("%s", message_errer);
        while ((i = getchar()) != '\n' && i != EOF)
            ;
    }
    return reel;
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
    animal.poids = saisir_reel("Poids :", "erreur de saisir [0-9]: ");
    animal.age = saisir_entier_positif("Age :", "erreur de saisir [0-9]: ", 100);
    animal.id = ID_ANIMAL_AUTO_INCREMENT++;
    COUNT_ANIMAL++;
    return animal;
}

void Afficher_animal(Animal animal)
{
    printf("|%-5d", animal.id);
    printf("|%-15s", animal.nom);
    printf("|%-15s", animal.espece);
    printf("|%-5d", animal.age);
    printf("|%-15s", animal.habitat);
    printf("|%-10.2f|\n", animal.poids);
}

void Ajouter_un_animal(Animal animal[])
{
    printf("\n========= <Animal ID: %d> ===========\n", COUNT_ANIMAL);
    getchar();
    animal[COUNT_ANIMAL] = cree_un_animal();
    clear();
    printf("\nl'animal ajoute avec succes !\n");
    header_de_tableau();
    Afficher_animal(animal[COUNT_ANIMAL - 1]);
    footer_de_tableau();
}

void Ajouter_plusieur_animaux(Animal animal[])
{
    char choix = 'y';
    do
    {
        switch (choix)
        {
        case 'y':
            Ajouter_un_animal(animal);
            break;
        case 'n':
            break;

        default:
            printf("choix invalide \n");
            break;
        }

        choix = saisir_caracter(" vieullez vous ajouter un autre animal [y/n]: ");
        clear();
    } while (choix != 'n');
}

void options_ajouter_un_animal(Animal animal[])
{
    int choix;
    clear();
    do
    {
        printf("============  Gestion du Zoo ========\n");
        printf("=============Options D'Ajout=========\n");
        printf("1. Ajouter un animal\n");
        printf("2. Ajouter plusieurs animaux\n");
        printf("0. Retourner au menu principal\n");

        choix = saisir_entier_positif("", " erreur de saisir [0-2]", 3);

        switch (choix)
        {
        case 1:
            clear();
            Ajouter_un_animal(animal);
            pause();
            choix = 0;
            break;
        case 2:
            clear();
            Ajouter_plusieur_animaux(animal);
            choix = 0;
            break;
        case 0:
            break;

        default:
            break;
        }
        clear();
    } while (choix != 0);
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
        animal[COUNT_ANIMAL].id = ID_ANIMAL_AUTO_INCREMENT;
        while (info_animal != NULL)
        {
            switch (mon_posion_dans_linge)
            {
            case 1:
                strcpy(animal[COUNT_ANIMAL].nom, info_animal);
                break;
            case 2:
                strcpy(animal[COUNT_ANIMAL].espece, info_animal);
                break;
            case 3:
                animal[COUNT_ANIMAL].age = atoi(info_animal);
                break;
            case 4:
                strcpy(animal[COUNT_ANIMAL].habitat, info_animal);
                break;
            case 5:
                animal[COUNT_ANIMAL].poids = atof(info_animal);
                break;
            default:
                break;
            }
            mon_posion_dans_linge++;
            info_animal = strtok(NULL, ",");
        }
        ID_ANIMAL_AUTO_INCREMENT++;
        COUNT_ANIMAL++;
    }
}

int habitat_existe(Animal animal[], char habitat[])
{
    for (int i = 0; i < COUNT_ANIMAL; i++)
        if (strcmp(animal[i].habitat, habitat) == 0)
            return 1;
    return 0;
}
int id_existe(Animal animal[], int id)
{
    for (int i = 0; i < COUNT_ANIMAL; i++)
        if (animal[i].id == id)
            return i;
    return -1;
}
int nom_existe(Animal animal[], char nom[])
{
    for (int i = 0; i < COUNT_ANIMAL; i++)
        if (strcmp(animal[i].nom, nom) == 0)
            return 1;
    return 0;
}
int espece_existe(Animal animal[], char espece[])
{
    for (int i = 0; i < COUNT_ANIMAL; i++)
        if (strcmp(animal[i].espece, espece) == 0)
            return 1;
    return 0;
}

void Afficher_tous_les_animaux(Animal animal[], char message[])
{

    printf("%s", message);
    header_de_tableau();
    for (int i = 0; i < COUNT_ANIMAL; i++)
        Afficher_animal(animal[i]);
    footer_de_tableau();
}
void trie_animaux_par_id(Animal animal[])
{
    int changment = 1;
    while (changment)
    {
        changment = 0;
        for (int i = 0; i < COUNT_ANIMAL - 1; i++)
        {
            if (animal[i].id > animal[i + 1].id)
            {
                Animal tmp = animal[i];
                animal[i] = animal[i + 1];
                animal[i + 1] = tmp;
                changment = 1;
            }
        }
    }
}

void trie_animaux_par_nom(Animal animal[])
{
    int changment = 1;
    while (changment)
    {
        changment = 0;
        for (int i = 0; i < COUNT_ANIMAL - 1; i++)
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
        for (int i = 0; i < COUNT_ANIMAL - 1; i++)
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
    if (habitat_existe(animal, habitat))
    {
        printf("----------------------les animaux d'habitat %s----------------------\n", habitat);
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (strcmp(animal[i].habitat, habitat) == 0)
                Afficher_animal(animal[i]);
        footer_de_tableau();
    }
    else
    {
        printf("\nAucun animal a cet habitat : %s  !\n", habitat);
    }
}

void options_affichage(Animal animal[])
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
        choix = saisir_entier_positif("", "\terreur de saisir!\n", 5);

        switch (choix)
        {
        case 1:
            clear();
            trie_animaux_par_id(animal);
            Afficher_tous_les_animaux(animal, " ---------la liste des animaux complet---------\n");
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
            Afficher_les_animaux_d_un_habitat_specefique(animal, saisir_chaine_de_caractere("Habitat: ", 20));
            pause();
            break;
        case 0:
            break;
        default:
            printf("choix invalide !\n");
            break;
        }

        clear();
    } while (choix != 0);
}

void Modifier_habitat_animal(Animal animal[], int id_modification)
{
    strcpy(animal[id_modification].habitat, saisir_chaine_de_caractere("Nouvel Habitat :", 20));
    printf("l'habitat modifier avec succes !\n");
}

void Modifier_age_animal(Animal animal[], int id_modification)
{
    animal[id_modification].age = saisir_entier_positif("Nouvel age :", " erreur de saisie !\n Age [0-100] :", 100);
    printf("l'age modifier avec succes !\n");
}

void options_modifier_un_animal(Animal animal[], int id_modification)
{
    int choix;
    do
    {
        printf("==================Gestion du Zoo ===============\n");
        printf("=========== Les options de Modification ===========\n");
        printf("1. Modifier l'habitat \n");
        printf("2. Modifier l'age\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("", "entree invalid [0-2] :", 3);
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

void Modifier_un_animal(Animal animal[], int select_id_pour_modifier)
{

    if (id_existe(animal, select_id_pour_modifier) != -1)
    {
        printf("\tvoici information d'animal id:%d\n", select_id_pour_modifier);
        header_de_tableau();
        Afficher_animal(animal[id_existe(animal, select_id_pour_modifier)]);
        footer_de_tableau();
        options_modifier_un_animal(animal, id_existe(animal, select_id_pour_modifier));
    }
    else
        printf("\tl'animal id:%d n'existe pas !\n", select_id_pour_modifier);
}

void Supprimer_un_animal(Animal animal[], int id_animal_supprimer)
{

    for (int i = 0; i < COUNT_ANIMAL - 1; i++)
        if (id_animal_supprimer == animal[i].id)
        {
            for (int j = i; j < COUNT_ANIMAL - 1; j++)
                animal[j] = animal[j + 1];
            COUNT_ANIMAL--;
        }
}

void options_de_supprimer(Animal animal[])
{
    char choix;
    int id_select_pour_supprimer = saisir_entier_positif("ID :", "entree invalid [0-9]: ", 10000000);
    if (id_existe(animal, id_select_pour_supprimer) != -1)
    {
        printf("\tvoici information d'animal id:%d\n", id_select_pour_supprimer);
        header_de_tableau();
        Afficher_animal(animal[id_existe(animal, id_select_pour_supprimer)]);
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
    int id = saisir_entier_positif("ID : ", "Ce ID n'existe pas !\n", ID_ANIMAL_AUTO_INCREMENT);
    if (id_existe(animal, id) != -1)
    {
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (animal[i].id == id)
                Afficher_animal(animal[i]);
        footer_de_tableau();
    }
    else
        printf("Ce ID n'existe pas\n");
}
void Rechercher_par_nom(Animal animal[])
{
    char *nom = saisir_chaine_de_caractere("Nom :", 20);
    if (nom_existe(animal, nom))
    {
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (strcmp(animal[i].nom, nom) == 0)

                Afficher_animal(animal[i]);
        footer_de_tableau();
    }
    else
        printf("\tNom:%s de l'animal n'existe pas !\n", nom);
}
void Rechercher_par_espece(Animal animal[])
{
    char *espece = saisir_chaine_de_caractere("Espece :", 20);

    if (espece_existe(animal, espece))
    {
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (strcmp(animal[i].espece, espece) == 0)

                Afficher_animal(animal[i]);
        footer_de_tableau();
    }

    else
        printf("\tEspece:%s de l'animal n'existe pas !\n", espece);
}
void options_Rechercher_un_animal(Animal animal[])
{
    int choix;

    do
    {
        printf("============ Gestion du Zoo ============\n");
        printf("============ Options de Recherche=========\n");
        printf("1. Rechercher par ID. \n");
        printf("2. Rechercher par Nom.\n");
        printf("3. Rechercher par Espece\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("", "erreur de saisie!\n", 4);

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
float trouver_age_moyenne(Animal animal[])
{
    int sum = 0;
    for (int i = 0; i < COUNT_ANIMAL; i++)
        sum += animal[i].age;
    return (float)sum / (float)(COUNT_ANIMAL - 1);
}
Animal Plus_vieux_animal(Animal animal[])
{
    Animal animal_vieux = animal[0];

    for (int i = 1; i < COUNT_ANIMAL; i++)
        if (animal[i].age > animal_vieux.age)
            animal_vieux = animal[i];
    return animal_vieux;
}

Animal Plus_jeune_animal(Animal animal[])
{
    Animal animal_jeune = animal[0];

    for (int i = 1; i < COUNT_ANIMAL; i++)
        if (animal[i].age < animal_jeune.age)
            animal_jeune = animal[i];
    return animal_jeune;
}

void especes_les_plus_reprsentees(Animal animal[])
{
    int count = 0, max = 0;

    char espece_reprsentee[20];
    for (int i = 0; i < COUNT_ANIMAL; i++)
    {
        for (int j = 0; j < COUNT_ANIMAL; j++)
            if (strcmp(animal[i].espece, animal[j].espece) == 0)
                count++;
        if (max < count)
        {
            max = count;
            strcpy(espece_reprsentee, animal[i].espece);
        }
        count = 0;
    }
    printf("|======================================================================|\n");
    printf("|%-20s              %-3dfois                             |\n", espece_reprsentee, max);
    printf("|______________________________________________________________________|\n");
}
void Statistiques(Animal animal[])
{
    printf("________________________________________________________________________\n");

    printf("|========================= Gestion du Zoo =============================|\n");
    printf("|========================== Statistiques ==============================|\n");
    printf("|======================================================================|\n");
    printf("|======================================================================|\n");
    printf("|Total animaux               %-10d                                |\n", COUNT_ANIMAL - 1);
    printf("|======================================================================|\n");
    printf("|Moyenne age                 %-10.2f ans                            |\n", trouver_age_moyenne(animal));
    printf("|======================================================================|\n");
    printf("|===========================Animal Plus Vieux==========================|\n");
    header_de_tableau();
    Afficher_animal(Plus_vieux_animal(animal));
    printf("|======================================================================|\n");
    printf("|=========================Animal Plus Jeune============================|\n");
    header_de_tableau();
    Afficher_animal(Plus_jeune_animal(animal));
    printf("|======================================================================|\n");
    printf("|=================especes les plus representees========================|\n");
    especes_les_plus_reprsentees(animal);
}
void menu_affichage_principale(Animal animal[])
{

    int choix;

    do
    {
        printf("========= Gestion du Zoo ========\n");
        printf("=========Menu Principal=========\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux\n");
        printf("3. Modifier un animal\n");
        printf("4. Supprimer un animal\n");
        printf("5. Rechercher un animal\n");
        printf("6. Statistiques\n");
        printf("0. Quitter\n");
        choix = saisir_entier_positif("", "\nerreur de saisir\n", 6);
        getchar();
        switch (choix)
        {
        case 1:
            clear();
            options_ajouter_un_animal(animal);
            break;
        case 2:
            clear();
            options_affichage(animal);
            break;
        case 3:
            clear();

            Modifier_un_animal(animal, saisir_entier_positif("ID :", "entree invalid [0>?]: ", ID_ANIMAL_AUTO_INCREMENT)); // 121212
            break;
        case 4:
            clear();
            options_de_supprimer(animal);
            break;
        case 5:
            clear();
            options_Rechercher_un_animal(animal);
            break;
        case 6:
            clear();
            Statistiques(animal);
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
    Animal a[Nomnre_max_animaux];
    fichier_to_tableau_animaux(a);

    menu_affichage_principale(a);
    return 0;
}
