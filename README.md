# 🦁 Gestion d'un Zoo en C

Une application console développée en langage **C** permettant de gérer les animaux d’un zoo.  
Le programme offre plusieurs fonctionnalités : ajout, modification, suppression, recherche, tri et statistiques.

---

## ✨ Fonctionnalités principales

- **Ajouter un animal** avec ses informations : nom, espèce, âge, habitat, poids.
- **Afficher tous les animaux** dans un tableau formaté.
- **Trier les animaux** :
  - Par nom (ordre alphabétique).
  - Par âge (croissant).
- **Rechercher un animal** :
  - Par ID.
  - Par nom.
  - Par espèce.
- **Modifier un animal** :
  - Modifier son habitat.
  - Modifier son âge.
- **Supprimer un animal** par ID.
- **Statistiques** :
  - Nombre total d’animaux.
  - Âge moyen des animaux.
  - Plus vieux animal.
  - Plus jeune animal.
  - Espèce la plus représentée.

---

## 📂 Organisation des fichiers

- `animaux.csv` : fichier source contenant les données initiales des animaux sous format CSV.
- `main.c` : code source principal de l’application.

Exemple de contenu `animaux.csv` :
```csv
1,Simba,Lion,5,Savane,190.5
2,Nala,Lion,4,Savane,175.0
3,ShereKhan,Tigre,8,Jungle,220.3
4,Baloo,Ours,12,Forêt,310.0
```

---

## ⚙️ Compilation et exécution

### Sous Linux / Mac :
```bash
gcc main.c -o zoo
./zoo
```

### Sous Windows :
```powershell
gcc main.c -o zoo.exe
zoo.exe
```

---

## 🖥️ Aperçu du programme

### Menu principal :
```
========= Gestion du Zoo ========
=========Menu Principale=========
1. Ajouter un animal
2. Afficher les animaux
3. Modifier un animal
4. Supprimer un animal
5. Rechercher un animal
6. Statistiques
0. Quitter
```

### Exemple d’affichage des animaux :
```
------------------------------------------------------
ID   |NOM       |ESPECE    |AGE  |HABITIT   |POIDS     
------------------------------------------------------
0    |Simba     |Lion      |5    |Savane    |190.50    
1    |Nala      |Lion      |4    |Savane    |175.00    
2    |ShereKhan |Tigre     |8    |Jungle    |220.30    
3    |Baloo     |Ours      |12   |Forêt     |310.00    
------------------------------------------------------
```

---

## 🚀 Améliorations possibles

- Sauvegarde automatique des données modifiées dans `animaux.csv`.
- Utilisation de fichiers binaires pour de meilleures performances.
- Interface graphique (ex: GTK ou Qt).
- Gestion des erreurs plus robuste.

---

## 👨‍💻 Auteur

Projet développé en **C** dans le cadre d’un apprentissage pratique de la gestion de données et des structures en programmation procédurale.
