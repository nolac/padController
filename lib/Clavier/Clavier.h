
/*
Clavier sous forme de matrice de boutons.

instancier avec:
nombre de lignes,
nombre de colonnes,

dans le setup:
objet.init(pinX,pinY,tableauDeValeurDesTouches[5][5])
!!! le tableau multidimensionnel en argulment doit
obligatoirement etre de taille de "tableau[x][x]"


//////////////////////////////////////////////////////////


buttons matrix keypad.

Constructor with :
number of rows
number of colulns

in setup :
objet.init(pinX,pinY,tableauDeValeurDesTouches[5][5])

!!!  the multidimensional array HAS TO BE
*/

#include "Arduino.h"

class Clavier
{
  public:
  // constructeurs
  Clavier(byte lignes, byte colonnes);
  Clavier(byte lignes,byte colonnes, byte pinX[], byte pinY[]);

  // destructeur


  //methodes
  void init();
  void init(byte tableau[5][5]);
  byte saisie();


  //methodes de test
//  int getLignes();
//  int getColonnes();
//  void getPinX();
//  void getPinY();
//  void getKeypad();

  private:
  //attributs
  byte m_nbLignes;
  byte m_nbColonnes;

  byte m_pinLignes[20];
  byte m_pinColonnes[20];

  bool m_isActive;

  byte m_tableauSortie[15][15];



};
