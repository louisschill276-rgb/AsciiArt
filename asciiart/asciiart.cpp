#ifdef _WIN32
#include <Windows.h>
#endif

#include "fichier.h"

int main(int argc,char* argv[])
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

	//recherche de l'element --help dans le tableau d'argument :
	bool help = afficherhelp(argc,argv);
	if (help)
		return 0;
	
	//recherche de l'element --input dans le tableau d'argument
    std::string nompgm;
    bool input = false;
    for (size_t i = 0; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--input")
        {
			if (i+1 < argc) {
				nompgm = argv[i + 1];
				input = true;
			}
			else {
				std::cerr << "Erreur : argument manquant";
			}
            
        }
    }
    if (!input)
    {
        std::cout << "donne le nom du fichier pgm avec extension : ";
        std::cin >> nompgm;
    }


    // instanciation de la palette :
    std::string nom_palette;
	bool inputpalette = false;
	for (size_t i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "--palette")
		{
			if (i + 1 < argc) {
				nom_palette = argv[i + 1];
				inputpalette = true;
			}
			else {
				std::cerr << "Erreur : argument manquant";
			}
		}
	}
	if (!inputpalette)
	{
        nom_palette = "palette.txt";
	}

    // stockage de la largeur et de la hauteur dans un array d'entier taille :
    std::string taile;
	taile = tailleimage(nompgm);
    std::array<int, 2> taille;
    std::stringstream ss(taile);
    ss >> taille[0] >> taille[1];
    
	// recuperation du nom du fichier texte rendu :
	std::string nomFichierAscii="";
	bool output = false;
	for (size_t i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "--output")
		{
			if (i + 1 < argc) {
				nomFichierAscii = argv[i + 1];
				output = true;
			}
			else {
				std::cerr << "Erreur : argument manquant";
			}

			
		}
	}

    // affichage :
    image(taille[0], taille[1] , nom_palette, nompgm, nomFichierAscii, output);

	return 0;
}