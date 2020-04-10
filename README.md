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
Afin de compiler sur le Raspberry, il faut d'abord se munir d'un nouveau compilateur croisé, disponible ici : 

[Cross-gcc-9.2.0-pi_3B.tar.gz](https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%209.2.0/Raspberry%20Pi%203A%2B%2C%203B%2B%2C%204/cross-gcc-9.2.0-pi_3%2B.tar.gz/download)

(Obtenus grâce à : https://github.com/abhiTronixraspberry-pi-cross-compilers)

Il faut ensuite extraire le dossier à la racine du projet, vous devriez alors avoir une architecture ressemblante à celle-ci :

```
HerosDeLaGuitare2i/
    --- bin/
    --- cross-pi-gcc-9.2.0-2/
    --- include/
    --- libs/
    --- ...
```

Enfin, il suffit de lancer la commande suivante à la racine du projet :

```bash
make rpi 
```

Pour transfèrer sur le rpi : 
```bash
scp -r bin/ pi@<IP_RPI>:~/HerosDeLaGuitare2i
scp -r ressources/ pi@<IP_RPI>:~/HerosDeLaGuitare2i
```

Pour finir, on execute le fichier : 
```bash
./bin/main_rpi.exe
```

## Exemples 

Pour compiler et transferer les examples fournis avec les libs (Buzzer, matrice et segments) :

```bash
make examples
```
Il faudra surement changer l'IP dans les makefile des exemples 



