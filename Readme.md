# Projet Raven
## UQAC trimestre automne 2017 - Cours IA jeux vidéo (8IAR125)

### Membres

Esmé James - JAME15539504
<br/>Paul Michaud - MICP25059508
<br/>Théo Debay - DEBT17049500
<br/>Rénald Morice - MORR14029503
<br/>Wilfried Pouchous - POUW04069501

### Dossier "Raven"

Contient le code source du TP ainsi que l'exécutable


### Modifications réalisées par rapport au code source initial

1) Modification de la classe Weapon_RocketLauncher : ajout de règles pour les variables floues (distance à la cible, état des munitions, désirabilité) de l'arme de type RocketLauncher. Ces variables possèdent désormais 5 ensembles


    * Weapon_RocketLauncher.cpp

2) Création class Raven_Bot_Learner :

    * Besoin de savoir quand un bot a tiré ou a voulu tiré -> création d'un membre de raven_bot 
  qu'on met a true quand on a voulu tiré, il sera remit à false quand le learner aura aprit de ce cas la
    * A chaque update du learner on sauvegarde les infos des/d'un autres bots (VITESSE DISTTOTARGET AMMO TIMEVISIBLE HASFIRED)
    * Dans le constructeur de rbl (raven bot learner) on créé un jeu de donnée d'apprentissage en fonction des données sauvegardés au préalable
    * Instanciation du perceptron + création du model ds le cstr
    * test du model avec un autre jeu de donné  ds le cstr

3) Modification de la classe Raven_WeaponSystem  : ajout d'un comportement flou lorsqu'un agent tire. La méthode ajoutée "InitializeFuzzyModule()" contient les éléments définissant cette logique floue. La méthode "AddNoiseToAim()" a été modifiée pour modifier la précision en fonction de la logique floue nouvellement implémentée. Les variables considérées pour cette logique floue sont :

    * la vitesse de l'agent
    * la distance de la cible
    * le temps depuis lequel la cible est visible

4) Introduction d'un joueur humain dans le jeu (choix d'une arme si elle est possédée par le joueur, déplacement au clavier). Classe(s) modifiée(s) : Raven_Bot, Raven_Game.

