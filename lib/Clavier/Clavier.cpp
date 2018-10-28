/*

Clavier sous forme de matrice de boutons.

instancier avec:
nombre de lignes,
nombre de colonnes,

dans le setup:
objet.init(pinX,pinY,tableauDeValeurDesTouches[5][5])
!!! le tableau multidimensionnel en argulment doit
obligatoirement etre de taille de "tableau[x][x]"

*/


#include "Clavier.h"

///////  constructeur  /////

Clavier::Clavier(byte lignes,byte colonnes)
 {
    m_nbLignes=lignes;
    m_nbColonnes=colonnes;
 }

///////   constructeur avec numeros de pins   ///
Clavier::Clavier(byte lignes,byte colonnes, byte pinX[], byte pinY[])
{
    m_nbLignes=lignes;
    m_nbColonnes=colonnes;


   //// lignes en sortie, puis mise a l'etat bas
   for(byte i=0;i<m_nbLignes;i++)
   {
     m_pinLignes[i]=pinX[i];
     pinMode(m_pinLignes[i],OUTPUT);
     digitalWrite(m_pinLignes[i],LOW);
   }

   /// colonnes en entrée.
   for(byte c=0;c<m_nbColonnes;c++)
   {
     m_pinColonnes[c]=pinY[c];
     pinMode(m_pinColonnes[c],INPUT);
   }

   /// ecriture du tableau des valeurs de sortie par defaut

	if(lignes==5&&colonnes==5)
	{
		byte clavierDefaut[5][5]={
  					{17,18,19,20,21},
  					{ 1, 2, 3, 4,22},
 					{ 5, 6, 7, 8,23},
  					{ 9,10,11,12,24},
  					{13,14,15,16,25}
							};

		for(byte l=0;l<5;l++)
  		{
    		for(byte c=0;c<5;c++)
    			{
      			m_tableauSortie[l][c]=clavierDefaut[l][c];
    			}
   		}
	}

	else
	{
		  byte i=1;
  	for(byte l=0;l<m_nbLignes;l++)
  		{
    		for(byte c=0;c<m_nbColonnes;c++)
    			{
      			m_tableauSortie[l][c]=i;
      			i++;
    			}
   		}
	}
}

/////// destructeur ///




 //////////////////////////////////////////////////////////////////////////////
 ////////////   init avec un tableau 2D en argument
 ///////////    probleme : imperatif de mettre un tableau[5][5] en argument
 ///////////       lors de l'appel de la méthode.
 ///////////       il serait souhaitable de pouvoir envoyer un tableau [x][x]
 ///////////////////////////////////////////////////////////////////////////////
void Clavier::init()
	{
		byte clavierDefaut[5][5]={
  						{17,18,19,20,21},
  						{ 1, 2, 3, 4,22},
 						{ 5, 6, 7, 8,23},
  						{ 9,10,11,12,24},
  						{13,14,15,16,25}
							};

		for(byte l=0;l<5;l++)
  		{
    		for(byte c=0;c<5;c++)
    			{
      			m_tableauSortie[l][c]=clavierDefaut[l][c];
    			}
   		}

	}

void Clavier::init(byte tableau[5][5])
 {/// ecriture du tableau des valeurs de sortie
  for(byte l=0;l<m_nbLignes;l++)
  {
    for(byte c=0;c<m_nbColonnes;c++)
    {
      m_tableauSortie[l][c]=tableau[l][c];
    }
   }
 }


 byte Clavier::saisie()
 {
  byte retour;
  for(byte l=0;l<m_nbLignes;l++)
  {
    digitalWrite(m_pinLignes[l],HIGH);
    for(byte c=0;c<m_nbColonnes;c++)
    {
      bool isActive=digitalRead(m_pinColonnes[c]);
      if(isActive)
      {
        retour=m_tableauSortie[l][c];
      }
    }
    digitalWrite(m_pinLignes[l],LOW);
  }
  return retour;
 }


 ///////////////////////////////////////////////
 //////////          tests     /////////////////
 ///////////////////////////////////////////////

//
//int Clavier::getLignes()
//{
// return(m_nbLignes);
//}

//int Clavier::getColonnes()
//{
//  return(m_nbColonnes);
//}

//void Clavier::getPinX()
//{
// Serial.print(" X : ");
// for(int i=0;i<m_nbLignes;i++)
//  {
//    Serial.print(m_pinLignes[i]);
//    Serial.print(" ");
//  }
//  Serial.println();
//}

//void Clavier::getPinY()
//{
// Serial.print(" Y : ");
// for(int i=0;i<m_nbColonnes;i++)
//  {
//    Serial.print(m_pinColonnes[i]);
//    Serial.print(" ");
//  }
//  Serial.println();
//}


//void Clavier::getKeypad()
//{
// for(int l=0;l<m_nbLignes;l++)
//  {
//    for(int c=0;c<m_nbColonnes;c++)
//    {
//      Serial.print(m_tableauSortie[l][c]);
//      Serial.print("  ");
//    }
//    Serial.println();
//  }
//}
