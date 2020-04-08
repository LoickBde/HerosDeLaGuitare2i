# HerosDeLaGuitare2i
Guitar Hero en utilisant le Joy-Pi

## Installation

### Ubuntu 

Afin de compiler le projet sur Ubuntu (pour tester l'interface graphique), il suffit de lancer la commande suivante à la racine du projet :

```bash
make ubuntu
```

**Attention** :
Il faut alors installer les paquets concernant SDL2 :
```bash
sudo apt-get libsdl2-dev libsdl2-ttf-dev
```

### Raspberry : 
Afin de compiler sur le Raspberry il suffit de lancer la commande suivante à la racine du projet :

```bash
make rpi 
```

**Attention** : La compilation crash car nous n'avons pas réussi à cross-compiler sdl2-ttf

## Exemples 

Pour compiler et transferer les examples fournis avec les libs :

```bash
make examples
```
Il faudra surement changer l'IP dans les makefile des exemples 



