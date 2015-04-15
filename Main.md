# Cas d'utilisation #
Les cas d'utilisation:
  * Connexion
En jeu:
  * Jouer carte
  * Lancer une partie

# Architecture #

L'architecture est découpée de la sorte: Un Client avec un module interface graphique et un module réseau (client) qui sera le moyen de communication avec le serveur. On donne un message au client et c'est lui qui le transforme, l'envoie et récupère la réponse. La classe principale du client s'appelle partie (qui est en fait la classe instanciée au tout début et qui servira aussi de classe principale dans le menus).

Du côté serveur ça se passe un peu pareil, on a une classe principale qui gère des classes jeu qui contiendront toutes les informations sur les parties jouées sur le serveur et qui lie les client\_joueur qui sont des classes à définir selon les besoins du module réseau (dans cette classe on enregistrera des informations comme : IP des joueurs et tout ce qui sert à s'y connecter).