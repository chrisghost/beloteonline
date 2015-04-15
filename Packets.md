Id pour le packet\_client:
  1. Connexion
  1. Carte
  1. Reponse
  1. Couleur attout

```
struct packet_client // Structure pour les transferts de données
{
	int id;
	string log;
	int id_j;
	enum Valeur val;
	enum Couleur couleur;
	bool reponse;
	enum Couleur couleur_att;
};
```

Id pour le packet\_server:
  1. Joueur
  1. Message
  1. Carte
  1. Demande
  1. Atout
  1. Validation
  1. Cartes
  1. Points

```
	struct demande
	{
		int type; //1- prendre carte; 2- attout?; 3- joueur carte
	};

	struct cartes
	{
		int nb_cartes;//nombre de cartes dans le tableau
		struct carte carte[5];

	};
```