# So Long - Projet 42  


### 🌟 Objectif du projet  

Le but principal de **So Long** est de créer un petit jeu en 2D où le joueur peut se déplacer dans un labyrinthe, collecter des objets et atteindre une sortie pour gagner. Le projet fait appel à la bibliothèque graphique **MinilibX** (MLX) pour gérer l’affichage et les interactions.  

![Aperçu du jeu So Long](assets/image.png)  
*Un exemple de rendu du jeu So Long en cours d'exécution.*  


### 🕹️ Fonctionnalités  

Voici les fonctionnalités que le projet doit implémenter :  

1. **Lecture de la carte :**  
   - Le jeu utilise un fichier `.ber` pour définir le labyrinthe.  
   - La carte doit être bien formatée (rectangulaire, fermée par des murs, etc.).  

2. **Déplacement du joueur :**  
   - Le joueur peut se déplacer dans les quatre directions (haut, bas, gauche, droite).  
   - Les mouvements sont comptés et affichés.  

3. **Collecte d'objets :**  
   - Le joueur doit ramasser tous les objets (souvent représentés par des "C" sur la carte) avant d'atteindre la sortie.  

4. **Gestion de la sortie :**  
   - La sortie (souvent représentée par "E") n’est accessible qu’après avoir collecté tous les objets.  

5. **Affichage graphique :**  
   - Les éléments du jeu (joueur, murs, sol, objets, sortie) sont représentés par des textures ou des couleurs simples.  



## 🛠️ Technologies utilisées  

- **Langage :** C  
- **Bibliothèque graphique :** [MinilibX](https://github.com/42Paris/minilibx-linux)  
- **Compilation :** Makefile  
- **Norme :** Respect strict de la norme de 42.  

---

### 🚀 Comment exécuter le projet  

1. Clonez ce dépôt :  

   ```bash
   git clone https://github.com/votre-utilisateur/so_long.git
   cd so_long

2. Exécuter : 
   ```bash
   make
   ./so_long map/nom_de_la_carte.ber

