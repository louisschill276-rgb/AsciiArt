#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <array>
#include <cmath>


std::string palette(std::string nompalette);
std::string tailleimage(std::string nompgm);
void image(int largeur, int hauteur, std::string nom_palette,std::string nompgm, std::string nomFichierAscii, bool output);
bool afficherhelp(int argc,char* tab[]);
