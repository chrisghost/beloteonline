void**lancerjeu(void** argument)
{
> (static\_cast<Belotte**>(argument))->jeu();
> }**



> pthread\_t jeu;
> pthread\_create(&jeu, NULL, lancerjeu, b);





MainJoueur**p\_mains[4](4.md); for (int i=0; i < 4; i++) {**p\_mains[i](i.md) = MainJoueur(joueurs[i](i.md)); }