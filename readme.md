# Projet SVG en C

Ce projet permet de créer et de gérer des formes géométriques depuis un menu dans le terminal. On peut ajouter des cercles, des rectangles, des carrés, des ellipses et des lignes, puis modifier leurs dimensions ou leur position, changer leur couleur de remplissage et les supprimer.

Les formes sont conservées dans une liste pendant l’exécution du programme. L’option d’export les écrit dans un fichier SVG de 800 × 600 pixels, nommé `dessin.svg`.

Pendant le développement, j’ai notamment travaillé sur la création des formes, la gestion de la mémoire de leurs couleurs et la génération du fichier SVG.

## Compilation et lancement

Pour compiler le projet :

```sh
make build
```

Pour lancer le programme :

```sh
./projet_svg
```

On peut aussi utiliser `make run` pour compiler et lancer le programme.
 