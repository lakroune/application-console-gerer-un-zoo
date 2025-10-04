#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nom[20];
    char espece[20];
    int age;
    char habitat[20];
    float poids;
} Animal;

int COUNT_ANIMAL = 0;
int ID_ANIMAL_AUTO_INCREMENT = 1;
int Nombre_max_animaux = 1000;
int Nombre_max_animaux_s;
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

char *coverte_premier_caracter_en_majuscule(char *chaine)
{
    if (chaine[0] >= 'a' && chaine[0] <= 'z')
        chaine[0] = chaine[0] - ('a' - 'A');
    for (size_t i = 1; i < strlen(chaine); i++)
        if (chaine[i] >= 'A' && chaine[i] <= 'Z')
            chaine[i] = chaine[i] + ('a' - 'A');
    return chaine;
}

Animal *changer_taille_tableau(Animal animal[], int size)
{
    Animal *new_animal = realloc(animal, (Nombre_max_animaux + size) * sizeof(Animal));
    if (new_animal == NULL)
    {
        printf("Erreur de reallocation de memoire\n");
        return animal;
    }
    Nombre_max_animaux += size;
    return new_animal;
}

Animal cree_un_animal()
{
    Animal animal;
    strcpy(animal.nom, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Nom Animal :", 20)));
    strcpy(animal.espece, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Espece :", 20)));
    strcpy(animal.habitat, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Habitat :", 20)));
    animal.poids = saisir_reel("Poids :", "erreur de saisie [0-2000]: ");
    animal.age = saisir_entier_positif("Age :", "erreur de saisie [0-100]: ", 100);
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
        printf("============  Gestion ZOO ========\n");
        printf("=============Options D'Ajout=========\n");
        printf("1. Ajouter un animal\n");
        printf("2. Ajouter plusieurs animaux\n");
        printf("0. Retourner au menu principal\n");

        choix = saisir_entier_positif("choix :", "erreur de saisie [0-2]\n", 2);

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
int fichier_to_tableau_animaux(Animal animal[], char nom_fichier[])
{
    FILE *fichier;
    char ligne[200];
    fichier = fopen(nom_fichier, "r");
    int pointer_sur_ligne = 1;
    int format = 1;
    if (fichier == NULL)
    {
        printf("fichier n'existe pas\n");
        return 0;
    }
    int nombre_entrer;
    while ((nombre_entrer = fscanf(fichier, "%[^,],%[^,],%d,%[^,],%f\n", animal[COUNT_ANIMAL].nom, animal[COUNT_ANIMAL].espece, &animal[COUNT_ANIMAL].age, &animal[COUNT_ANIMAL].habitat, &animal[COUNT_ANIMAL].poids)) != EOF)
    {
        if (nombre_entrer == 5)
        { // vérifier si toutes les valeurs sont lues correctement
            strcpy(animal[COUNT_ANIMAL].nom, coverte_premier_caracter_en_majuscule(animal[COUNT_ANIMAL].nom));
            strcpy(animal[COUNT_ANIMAL].espece, coverte_premier_caracter_en_majuscule(animal[COUNT_ANIMAL].espece));
            strcpy(animal[COUNT_ANIMAL].habitat, coverte_premier_caracter_en_majuscule(animal[COUNT_ANIMAL].habitat));
            animal[COUNT_ANIMAL++].id = ID_ANIMAL_AUTO_INCREMENT++;
        }
        else
        {
            if (format)
                printf("forme de fichier doit etre comme suite\nnom,ecpece,age,habitat,poid\n");
            printf("Format de ligne incorrect, saut de la ligne %d.\n", pointer_sur_ligne);
            fgets(ligne, sizeof(ligne), fichier); // lire et ignorer la ligne incorrect
            format = 0;
        }
        pointer_sur_ligne++;
    }

    fclose(fichier);
    return 1;
}

void fichier_to_tableau_animaux_binaire(Animal animal[])
{
    FILE *fichier;
    fichier = fopen("animaux", "rb");
    if (fichier == NULL)
    {
        printf("erreur d'ouverture fichier");
    }
    else
        printf("les donnees sont chargees avec succes !\n");
    fread(&Nombre_max_animaux_s, sizeof(int), 1, fichier);
    // animal = changer_taille_tableau(animal, Nombre_max_animaux_s);
    fread(&ID_ANIMAL_AUTO_INCREMENT, sizeof(int), 1, fichier);
    while (fread(&animal[COUNT_ANIMAL], sizeof(Animal), 1, fichier))
        COUNT_ANIMAL++;

    fclose(fichier);
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
        printf("========= Gestion ZOO ========\n");
        printf("=========Options D'Affichage=========\n");
        printf("1. Afficher la liste des animaux complet \n");
        printf("2. Trier par nom d'un animal\n");
        printf("3. Trier par age d'un animal\n");
        printf("4. Afficher les animaux d'un habitat specefique\n");
        printf("0. retour le menu Principale\n");
        choix = saisir_entier_positif("choix :", "erreur de saisie [0-4]\n", 4);

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
            Afficher_les_animaux_d_un_habitat_specefique(animal, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Habitat :", 20)));
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
    strcpy(animal[id_modification].habitat, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Nouvel Habitat :", 20)));
    printf("l'habitat modifier avec succes !\n");
}

void Modifier_age_animal(Animal animal[], int id_modification)
{
    animal[id_modification].age = saisir_entier_positif("Nouvel Age :", " erreur de saisie !\n Age [0-100] :", 100);
    printf("l'age modifier avec succes !\n");
}

void options_modifier_un_animal(Animal animal[], int id_modification)
{
    int choix;
    do
    {
        printf("==================Gestion ZOO ===============\n");
        printf("=========== Les options de Modification ===========\n");
        printf("1. Modifier l'habitat \n");
        printf("2. Modifier l'age\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("choix :", "entree invalid [0-2] :", 2);
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
    {
        printf("\tl'animal id:%d n'existe pas !\n", select_id_pour_modifier);
        pause();
    }
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
    int id_select_pour_supprimer = saisir_entier_positif("ID :", "ID n'existe pas [0>?]: ", ID_ANIMAL_AUTO_INCREMENT);
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
                printf("l'animal de ID:%d ete supprime !\n", id_select_pour_supprimer);
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
    {
        printf("\tl'animal id:%d n'existe pas !\n", id_select_pour_supprimer);
        pause();
    }
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
    char *nom = coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Nom :", 20));
    if (nom_existe(animal, nom))
    {
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (strcmp(animal[i].nom, nom) == 0)
                Afficher_animal(animal[i]);
        footer_de_tableau();
    }
    else
        printf("\tNom:\"%s\" de l'animal n'existe pas !\n", nom);
}
void Rechercher_par_espece(Animal animal[])
{
    char *espece = coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Espece :", 20));

    if (espece_existe(animal, espece))
    {
        header_de_tableau();
        for (int i = 0; i < COUNT_ANIMAL; i++)
            if (strcmp(animal[i].espece, espece) == 0)

                Afficher_animal(animal[i]);
        footer_de_tableau();
    }

    else
        printf("\tEspece:\"%s\" de l'animal n'existe pas !\n", espece);
}
void options_Rechercher_un_animal(Animal animal[])
{
    int choix;

    do
    {
        printf("============ Gestion ZOO ============\n");
        printf("============ Options de Recherche=========\n");
        printf("1. Rechercher par ID. \n");
        printf("2. Rechercher par Nom.\n");
        printf("3. Rechercher par Espece\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("choix :", "erreur de saisie![0-3]\n", 3);

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

void remplir_avec_zero(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void trie_les_especes_selon_leur_nombre(char especes[][20], int count_espece[], int nombre_espece_different)
{
    for (int i = 0; i < nombre_espece_different - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < nombre_espece_different; j++)
        {
            if (count_espece[j] > count_espece[max_index])
            {
                max_index = j;
            }
        }
        if (max_index != i)
        {
            int temp_count = count_espece[i];
            count_espece[i] = count_espece[max_index];
            count_espece[max_index] = temp_count;

            char temp_espece[20];
            strcpy(temp_espece, especes[i]);
            strcpy(especes[i], especes[max_index]);
            strcpy(especes[max_index], temp_espece);
        }
    }
}

void les_trois_especes_les_plus_representees(Animal animal[])
{
    int count_espece[COUNT_ANIMAL];
    char especes[COUNT_ANIMAL][20];
    int nombre_espece_different = 0;

    if (COUNT_ANIMAL <= 0)
    {
        printf("Aucun animal dans le zoo !\n");
        return;
    }

    remplir_avec_zero(count_espece, COUNT_ANIMAL);
    // Comptage par espèce
    strcpy(especes[nombre_espece_different], animal[0].espece);
    count_espece[nombre_espece_different++]++;

    for (int i = 1; i < COUNT_ANIMAL; i++)
    {
        int existe = 0;
        for (int j = 0; j < nombre_espece_different; j++)
        {
            if (strcmp(animal[i].espece, especes[j]) == 0)
            {
                count_espece[j]++;
                existe = 1;
                break;
            }
        }
        if (!existe)
        {
            strcpy(especes[nombre_espece_different], animal[i].espece);
            count_espece[nombre_espece_different++]++;
        }
    }

    // Trier les espèces selon leur nombre (tri par sélection)
    trie_les_especes_selon_leur_nombre(especes, count_espece, nombre_espece_different);

    // Afficher les trois premières
    printf("============ Gestion ZOO ============\n");
    printf("========= Option statistiques ========\n");
    printf("===== Especes les plus representees =====\n");

    int limite = (nombre_espece_different < 3) ? nombre_espece_different : 3;
    for (int k = 0; k < limite; k++)
    {
        printf("%d. %s avec %d animaux\n", k + 1, especes[k], count_espece[k]);
    }
}

void total_animaux(Animal animal[])
{
    printf("============ Gestion ZOO ============\n");
    printf("=========option statistiques=========\n");
    printf("=============Total animaux=============\n");
    printf(". total animaux :%d ans\n", COUNT_ANIMAL);
}

void moyenne_age(Animal animal[])
{

    float moyenne_age = trouver_age_moyenne(animal);
    int annee = moyenne_age;
    int moins = (moyenne_age - annee) * 12;
    printf("============ Gestion ZOO ============\n");
    printf("=========option statistiques=========\n");
    printf("=============Moyenne Age=============\n");
    if (annee > 0 && moins > 0)
        printf(". Moyenne Age :%d ans+ %d moins\n", annee, moins);
    else if (annee > 0 && moins == 0)
        printf(". Moyenne Age :%d ans\n", annee);
    else
        printf(". Moyenne Age :%d moins\n", moins);
}
void animal_plus_vieux(Animal animal[])
{
    Animal animal_vieux = Plus_vieux_animal(animal);
    printf("============ Gestion ZOO ============\n");
    printf("=========option statistiques=========\n");
    printf("=============Animal Plus Vieux=============\n");
    header_de_tableau();
    Afficher_animal(animal_vieux);
    footer_de_tableau();
}
void animal_plus_jeune(Animal animal[])
{
    Animal animal_jeune = Plus_jeune_animal(animal);
    printf("============ Gestion ZOO ============\n");
    printf("=========option statistiques=========\n");
    printf("=============Animal Plus Jeune=============\n");
    header_de_tableau();
    Afficher_animal(animal_jeune);
    footer_de_tableau();
}

void option_statistiques(Animal animal[])
{

    int choix;

    do
    {
        printf("============ Gestion ZOO ============\n");
        printf("============option statistiques=========\n");
        printf("1. Total animaux . \n");
        printf("2. Moyenne age .\n");
        printf("3. Animal Plus Vieux .\n");
        printf("4. Animal Plus Jeune .\n");
        printf("5. especes les plus representees .\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("choix :", "erreur de saisie![0-5]\nchoix :", 5);

        switch (choix)
        {
        case 1:
            clear();
            total_animaux(animal);
            pause();
            break;

        case 2:
            clear();
            moyenne_age(animal);
            pause();
            break;
        case 3:
            clear();
            animal_plus_vieux(animal);
            pause();
            break;
        case 4:
            clear();
            animal_plus_jeune(animal);
            pause();
            break;
        case 5:
            clear();
            les_trois_especes_les_plus_representees(animal);
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

void sauvegarder_donnees_dans_fichier_binaire(Animal animal[])
{
    FILE *fichier;
    fichier = fopen("animaux", "wb");
    if (fichier == NULL)
    {
        printf("erreur d'ouverture fichier");
    }
    else
        printf("les donnees sont sauvegardees avec succes !\n");
    Nombre_max_animaux_s = COUNT_ANIMAL;
    fwrite(&Nombre_max_animaux_s, sizeof(int), 1, fichier);
    fwrite(&ID_ANIMAL_AUTO_INCREMENT, sizeof(int), 1, fichier);
    for (int i = 0; i < COUNT_ANIMAL; i++)
        fwrite(&animal[i], sizeof(Animal), 1, fichier);

    fclose(fichier);
}
void option_quiter(Animal animal[])
{
    char choix = 'y';
    do
    {
        choix = saisir_caracter("vieullez vous sauvegarder les donnees avant de quitter [y/n]: ");
        switch (choix)
        {
        case 'y':
            clear();
            sauvegarder_donnees_dans_fichier_binaire(animal);
            printf("les donnees sont sauvegardees avec succes !\n");
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
void exporter_donnees_dans_fichier_csv(Animal animal[])
{
    FILE *fichier;
    char nomfichier[50];
    strcpy(nomfichier, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Nom du fichier :", 45)));
    strcat(nomfichier, ".csv");
    fichier = fopen(nomfichier, "w");
    if (fichier == NULL)
    {
        printf("erreur d'ouverture fichier");
    }
    else
        printf("les donnees sont exportees avec succes !\n");
    fprintf(fichier, "ID,NOM,ESPECE,AGE,HABITAT,POIDS\n");
    for (int i = 0; i < COUNT_ANIMAL; i++)
        fprintf(fichier, "%d,%s,%s,%d,%s,%.2f\n", animal[i].id, animal[i].nom, animal[i].espece, animal[i].age, animal[i].habitat, animal[i].poids);
    fclose(fichier);
}

void importer_donnees_depuis_fichier_csv(Animal animal[])
{
    char nom_fichier[50];
    strcpy(nom_fichier, coverte_premier_caracter_en_majuscule(saisir_chaine_de_caractere("Nom du fichier.csv :", 45)));
    if (fichier_to_tableau_animaux(animal, nom_fichier) == 1)
        printf("les donnees sont importees avec succes !\n");
}

void options_importer_exporter(Animal animal[])
{
    int choix;
    do
    {
        printf("============ Gestion ZOO ============\n");
        printf("============ Options d'import/export=========\n");
        printf("1. Importer les donnees depuis un fichier csv\n");
        printf("2. Exporter les donnees vers un fichier csv\n");
        printf("0. Retourner au menu principal\n");
        choix = saisir_entier_positif("choix :", "erreur de saisie [0-2]\n", 2);

        switch (choix)
        {
        case 1:
            clear();
            importer_donnees_depuis_fichier_csv(animal);
            choix = 0;
            break;

        case 2:
            clear();
            exporter_donnees_dans_fichier_csv(animal);
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

    } while (choix != 0);
}

void information_programme()
{
    printf("============ Gestion ZOO ============\n");
    printf("============ A propos du programme =========\n");
    printf("Programme de gestion d'un zoo.\n");
    printf("Developpe par : Lakroune Ismail\n");
    printf("Version : 1.0\n");
    printf("Date : 2025\n");
    printf("Langage : C\n");
    printf("=======================================\n");
    printf("Plus d'informations :\n");
    printf("https://github.com/lakroune/application-console-gerer-un-zoo\n");
    printf("=======================================\n");
    printf("Details du projet :\n");
    printf("- Ajout, modification, suppression et recherche d'animaux.\n");
    printf("- Affichage des animaux avec tri par nom, age ou habitat.\n");
    printf("- Statistiques : total, moyenne d'age, plus vieux/jeune, especes les plus representees.\n");
    printf("- Import/export des donnees au format CSV et sauvegarde en binaire.\n");
    printf("- Interface simple en ligne de commande.\n");
    printf("- Gestion automatique des IDs et de la memoire.\n");
    printf("- Chargement et sauvegarde automatique des donnees au demarrage et a la fermeture.\n");
    printf("- Verification du format des fichiers lors de l'import.\n");
    printf("- Protection contre les erreurs de saisie et gestion des entrees invalides.\n");
    printf("- Affichage detaille des informations de chaque animal.\n");
    printf("- Tri dynamique des animaux selon plusieurs criteres.\n");
    printf("- Statistiques avancees sur les animaux du zoo.\n");
    printf("=======================================\n");
    printf("Merci d'utiliser ce programme !\n");
    pause();
}

void menu_affichage_principale(Animal animal[])
{

    int choix;

    do
    {
        printf("========= Gestion ZOO ========\n");
        printf("=========Menu Principal=========\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux\n");
        printf("3. Modifier un animal\n");
        printf("4. Supprimer un animal\n");
        printf("5. Rechercher un animal\n");
        printf("6. Statistiques\n");
        printf("7. inporter/Exporter les donnees\n");
        printf("8. A propos du programme\n");
        printf("0. Quitter\n");
        choix = saisir_entier_positif("choix :", "\nerreur de saisie [0-8]\n", 8);
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
            option_statistiques(animal);
            pause();
            break;
        case 7:
            clear();
            options_importer_exporter(animal);
            pause();
            break;
        case 8:
            clear();
            information_programme();
            break;

        case 0:
            option_quiter(animal);

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
    Animal *a = malloc(Nombre_max_animaux * sizeof(Animal));
    if (a == NULL)
    {
        printf("Erreur d'allocation de memoire\n");
        return 1;
    }

    // fichier_to_tableau_animaux(a);
    fichier_to_tableau_animaux_binaire(a); // charger les donnees depuis le fichier binaire

    menu_affichage_principale(a);
    return 0;
}
