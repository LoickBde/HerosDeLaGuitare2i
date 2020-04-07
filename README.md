# HerosDeLaGuitare2i
Guitar Hero en utilisant le Joy-Pi

## Installation
### Création des librairies (statiques)

Pour créer les librairies, executez la commande : 
```bash 
make library
```

### Utilisation des librairies 
Pour compiler en utilisant les libs de musique, 7segment et matrice : 
```bash
 $(CC) $(INC) $(LIB) source.c -o source -lmatrix -lmusic -lsegments
```

## Exemples 

Pour compiler et transferer les examples fournis avec les libs (mdp de pi: pi) :

```bash
make examples
```
Il faudra surement changer l'IP dans les makefile des exemples 



