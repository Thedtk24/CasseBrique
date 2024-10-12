Projet de Jeu Breakout

Vue d'ensemble

Ce projet est une implémentation du jeu Breakout en C, utilisant la bibliothèque SDL2. 

Le jeu consiste à contrôler une palette qui renvoie une balle pour casser des briques. L'objectif est de détruire toutes les briques sans laisser la balle tomber en dessous de la palette. Le jeu inclut des mécanismes de base tels que les collisions, un système de score, et des graphismes dynamiques.

Fonctionnalités

Collision Balle-Palette : La balle rebondit sur la palette et les briques.

Destruction des briques : Cassez des briques et gagnez des points à chaque coup.

Système de score : Affichage en temps réel du score du joueur.

Graphismes : Le jeu utilise des images d'arrière-plan et du texte pour afficher le score.

Technologies utilisées

Langage C

SDL2 pour le rendu graphique et la gestion des événements.

SDL_image pour charger les images PNG.

SDL_ttf pour le rendu des polices TrueType.


Installation

Prérequis

Assurez-vous d'avoir installé les bibliothèques suivantes sur votre système :

SDL2

SDL2_image

SDL2_ttf

Vous pouvez installer SDL et ses extensions avec ces commandes (pour Linux) :

"sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev"

Compilation

Un fichier Makefile est fourni pour faciliter la compilation du projet. 

Il suffit de lancer la commande suivante dans le répertoire du projet : "make"

Cela compilera le jeu et générera un fichier exécutable.

Lancer le Jeu

Après avoir compilé le projet, lancez le jeu avec la commande suivante :

./Breakout
