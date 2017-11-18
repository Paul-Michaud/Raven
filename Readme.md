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

1) Ajout de règles pour les variables floues (distance à la cible, état des munitions, désirabilité) de l'arme de type RocketLauncher. Ces variables possèdent désormais 5 ensembles. Fichier(s) modifié(s) :

    * Weapon_RocketLauncher.cpp

	
a)création class raven_bot_learner
b)besoin de savoir quand un bot a tiré ou a voulu tiré -> création d'un membre de raven_bot 
qu'on met a true quand on a voulu tiré, il sera remit à false quand le learner aura aprris de ce cas la
c)a chaque (?) update du learner on sauvegarde les infos des autres bots (VITESSE DISTTOTARGET  AMMO TIMEVISIBLE HASFIRED)