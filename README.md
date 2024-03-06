# Chomp
Jeu du Chomp

Le Jeu du Chomp est un jeu combinatoire abstrait à deux joueurs.

Règles du jeu 

Les règles du Chomp sont les suivantes. Deux joueurs se disputent une tablette de chocolat de dimension n × m où n et m sont des entiers supérieurs à un. 

<img width="125" alt="Capture d’écran 2024-03-06 à 17 43 12" src="https://github.com/EBlanchet/Chomp/assets/86469825/8171b203-282a-4f0d-b791-433feb1e9980">


FIGURE 1 – Une tablette de chocolat du Chomp 3 × 5 dans sa configuration initiale. Le carré empoisonné contient un point

Chaque joueur choisit alternativement un carré de chocolat, le mange, et mange aussi tous les carrés qui se trouvent en bas et à sa droite.

<img width="317" alt="Capture d’écran 2024-03-06 à 17 43 41" src="https://github.com/EBlanchet/Chomp/assets/86469825/e7be6cef-19b6-466a-ae40-e989bcdbb129">


FIGURE 2 – Le joueur mange un carré de chocolat — celui qui contient une croix ×. Cette action a l’effet de manger tous les carrés de chocolat situés en bas et à sa droite.

La partie s’arrête lorsque l’un des deux joueurs mange le carré de chocolat en position (0,0). Ce carré est en effet empoisonné et ce joueur perd la partie.

L'objectif est de parfaire l'utilisation de la bibliothèque NCURSES qui permet d’afficher la tablette de chocolat et de faire en sorte que deux joueurs puissent jouer au Chomp à la souris. On suit dans la conception de ce projet une approche ascendante (dite bottom-up). Celle-ci consiste à réaliser le projet en constituant une à une ses pièces pour les assembler finalement.

Notions utilisées

- Tableau statique à deux dimensions ;
- Type structuré ;
— Type énuméré ;
— Interface NCURSES en gestion au tour par tour ;
— Comparaison entre programmation par fichier unique et par modules ;
— Compilation par un script bash.

Modularisation

<img width="207" alt="image" src="https://github.com/EBlanchet/Chomp/assets/86469825/ae5095c1-f8a6-4e5f-abab-56d79d1e02f9">

Découpage :
tablette.c : type Tablette		* type et fonctions de la tablette de chocolat *
		    fonction creer_tablette
		    fonction manger

	joueur.c : type Joueur		* joueurs *
		 fonction adversaire

	position.c : include tablette.h	* tout ce qui est en rapport avec la position *
		    include joueur.h
		    include coup.h
		    define NB_LIGNES 8
		    define NB_COLONNES 16
		    type Position
		    fonction est_jeu_termine
		    fonction est_legal
		    fonction jouer_coup
		    fonction afficher_position
	coup.c : include position.h		* lecture du coup actuel *
	              type Coup
	              fonction lire_coup

La version modularisée a l’avantage d’être plus facilement modifiable et la détection des erreurs est plus évidente. En effet, le changement de taille de plateau ou encore l’ajout d’une version contre un ordinateur seront plus simple.
La version en un fichier unique a d’autres avantages, comme l’accès plus simple aux fonctions (pas de risque de doublons par exemple). Nous avons aussi remarqué que cela est plus simple a l’exécution, une commande suffit à faire fonctionner le programme.


