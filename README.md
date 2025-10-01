# Gestion Zoo en C

Une petite application en C permettant de **gérer un zoo** à partir d’un fichier `animaux.csv`.  
Les animaux y sont stockés avec leurs informations (id, nom, espèce, âge, habitat, poids).  
L'application permet de **charger**, **afficher**, **ajouter**, **supprimer**, **mettre à jour** et **rechercher** des animaux.


---

## Structure du projet

```
gestion-zoo/
│
├── gestion-zoo.c      # Code source principal
├── animaux.csv        # Fichier de données (liste des animaux)
├── test.exe           # Exécutable compilé (Windows)
└── README.md          # Documentation du projet
```

---

## Fonctionnalités

- Charger les animaux depuis un fichier CSV  
- Afficher la liste des animaux  
- Ajouter un nouvel animal  
- Supprimer un animal  
- Mettre à jour les informations d’un animal
- Rechercher un animal par ID ou par nom espece

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
id,nom,espece,age,habitat,poids
0,Lion1,Lion,12,Savane,190.5
...
30,Alex,Lion,11,Savane,210.0
```
---
## interface Utilisateur

``` 
bash
```plaintext
=============================
        GESTION ZOO             
=============================
1. Afficher tous les animaux
2. Ajouter un animal
3. Supprimer un animal
4. Mettre à jour un animal
5. Rechercher un animal par ID
6. Rechercher un animal par nom espece
7. Quitter
=============================
Choix:
```

---

## ✨ Auteur
Projet développé par **Lakroune** lien GitHub: [https://github.com/Lakroune](https://github.com/Lakroune)       
le 04/10/2023   projet de fin de formation C chez **youcode**.

---
