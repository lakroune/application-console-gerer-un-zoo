# Gestion Zoo en C

Une petite application en C permettant de **gérer un zoo** à partir d’un fichier `animaux`.  
Les animaux y sont stockés avec leurs informations (id, nom, espèce, âge, habitat, poids).  
L'application permet de **charger**, **afficher**, **ajouter**, **supprimer**, **mettre à jour** et **rechercher** des animaux.


---

## Structure du projet

```
gestion-zoo/
│
├── gestion-zoo.c      # Code source principal
├── animaux            # Fichier binaire pour stocker les animaux
├── test.exe           # Exécutable compilé (Windows)
├── README.md          # Documentation du projet
└── animaux.csv        # Fichier CSV contenant les données des animaux pour l'import/export
```

---

## Fonctionnalités

- Charger les animaux depuis un fichier CSV  
- Afficher la liste des animaux  
- Ajouter un nouvel animal  
- Supprimer un animal  
- Mettre à jour les informations d’un animal
- Rechercher un animal par ID ou par nom espece
- Importer/exporter les données au format CSV
- Interface utilisateur simple en ligne de commande
- Gestion des erreurs (fichier manquant, entrée invalide, etc.)
- Souvgarder les modifications dans le fichier binaires(animaux)


---

## Compilation

Pour compiler sous Windows (MinGW) :
```bash
gcc gestion-zoo.c -o test.exe
test.exe
```

---

## 📊 Exemple de contenu `animaux.csv`

```csv
nom,espece,age,habitat,poids
Lion1,Lion,12,Savane,190.5
...
Alex,Lion,11,Savane,210.0
```
---
## interface Utilisateur

``` 
bash
=============================
        GESTION ZOO             
=============================
1. Afficher tous les animaux
2. Ajouter un animal
3. Supprimer un animal
4. Mettre à jour un animal
5. Rechercher un animal par ID
6. Rechercher un animal par nom espece
7. Importer/exporter fichier csv
8. A propos du programme
0. Quitter

=============================
Choix: ?
```

---
bash
### A propos du programme
```
=============================
  A PROPOS DU PROGRAMME
=============================
Programme de gestion d'un zoo.
Developpe par : Lakroune Ismail
Version : 1.0
Date : 2025
Langage : C
=============================
```

## ✨ Auteur
Projet développé par **Lakroune** lien GitHub: [github](https://github.com/Lakroune) et [Gestion ZOO](https://github.com/lakroune/application-console-gerer-un-zoo)    
le 02/10/2023   projet de fin de formation C chez **youcode**.

---
