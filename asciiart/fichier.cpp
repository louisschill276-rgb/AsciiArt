#include "fichier.h"

/// <summary>
/// cette fonction ouvre le fichier palette choisi par l'utilisateur et le parcours pour le stocker dans un string
/// </summary>
/// <param name="nompalette"> un string comprenant le nom du fichier contenant la palette </param>
/// <returns> un string comprenant les elements de la palette a la suite</returns>
std::string palette(std::string nompalette) {
    // ouverture du fichier:
    std::ifstream fichier(nompalette);
    if (!fichier.is_open()) {
        std::cerr << "erreur impossible d'ouvrir le fichier";
    }

    // parcours du fichier :
    std::string ligne;
    std::string resultat;
    while (fichier)
    {
        std::getline(fichier, ligne); // recuperation de la paltte de couleur
        resultat += ligne;
    }

    return resultat;
}

/// <summary>
/// dette fonction va ouvrir l'image .pgm et chercher dans son entete sa largeur et sa hauteur pour la stocker dans un string
/// </summary>
/// <param name="nompgm"> un autre string comprenant le nouveau nom du fichier sans extention </param>
/// <returns> un string comprenant la largeur puis la hauteur de l'image en nombres de pixels</returns>
std::string tailleimage(std::string nompgm) {

    std::string nom_fichier = nompgm;

    // Ouverture de l'image .pgm en mode binaire :
    std::ifstream fichier(nom_fichier, std::ios_base::binary);
    if (!fichier.is_open()) {
        std::cerr << "erreur impossible d'ouvrir le fichier fonction tailleimage";
    }
    // parcours de l'entete :
    std::string taille;
    std::string donnes;
    for (int i = 0; i < 4; i++)
    {
        if (i == 2)
        {
            std::getline(fichier, taille); // recuperation de la largeur et de la longueur de l'image stocker dans l'entete
        }
        else
        {
            std::getline(fichier, donnes); // stockage des donner de l'entete qui ne servent pas 
        }
    }
    return taille;
}

/// <summary>
/// cette fonction va afficher dans la console l'image sous forme d'ascii artS
/// </summary>
/// <param name="largeur"> int contenant la largeur de l'image en pixels </param>
/// <param name="hauteur"> int contenant la longueur de l'image en pixels </param>
/// <param name="nom_palette"> un string comprenant le nom du fichier contenant la palette </param>
/// <param name="nompgm"> un autre string comprenant le nouveau nom du fichier sans extention </param>
/// <param name="nomFichierAscii">un string du nom de fichier .txt écrit par le programme</param>
/// <param name="output"> un booléen qui dit si oui ou non l'utilisateur a défini un fichier de sortie</param>
/// <returns>ne retourne rien</returns>
void image(int largeur,int hauteur,std::string nom_palette,std::string nompgm, std::string nomFichierAscii, bool output)
{
    // transformation de l'image :
    std::string nom_fichier = nompgm;
    // Ouverture de l'image .pgm en mode binaire :
    std::ifstream fichier(nom_fichier, std::ios_base::binary);
    if (!fichier.is_open()) {
        std::cerr << "erreur impossible d'ouvrir le fichier fonction image";
    }
    // calcul de la taille du fichier en pixels :
    int nombreDeOctets = largeur * hauteur;
    std::vector<char> donnees(nombreDeOctets);
    
    // on saute les 4 premières lignes de l'entêtes :
    std::string ligneEntete;
    for (int i = 0; i < 4; ++i) {
        std::getline(fichier, ligneEntete);
    }

    // stockage de l'image dans un vector :
    fichier.read(donnees.data(), nombreDeOctets);


    if (output) {
        // recuperation de la palette de couleur
        std::string palete = palette(nom_palette);

        // ecriture dans le fichier
        std::ofstream fichierAsciiArt(nomFichierAscii);

        // parcours de chaque pixels, i étant le i ème pixel
        for (size_t i = 0; i < nombreDeOctets; ++i) {

            // le char est entre -128 et 127, on le veut de 0 à 255 :
            unsigned char pixel = static_cast<unsigned char>(donnees[i]);

            // on calcul à quel caractère dans la palette le pixel correspond
            int indiceCaractere = pixel / 32;

            if (fichierAsciiArt.is_open()) {
                fichierAsciiArt << palete[indiceCaractere];
            }

            // quand on arrive à la fin de la ligne on saute une ligne dans l'affichage
            // si le i ème pixel est égale au nombre de la largeur de l'image alors on arrive au bout d'une ligne
            if (((i + 1) % largeur) == 0) {
                if (fichierAsciiArt.is_open()) {
                    fichierAsciiArt << "\n";
                }
            }

        }

    }
    else 
    {
        std::cout << "Image pgm en ASCII " << std::endl;

        // recuperation de la palette de couleur
        std::string palete = palette(nom_palette);

        // parcours de chaque pixels, i étant le i ème pixel
        for (size_t i = 0; i < nombreDeOctets; ++i) 
        {

            // le char est entre -128 et 127, on le veut de 0 à 255 :
            unsigned char pixel = static_cast<unsigned char>(donnees[i]);

            // on calcul à quel caractère dans la palette le pixel correspond
            int indiceCaractere = pixel / 32;

            std::cout << palete[indiceCaractere];

            // quand on arrive à la fin de la ligne on saute une ligne dans l'affichage
            // si le i ème pixel est égale au nombre de la largeur de l'image alors on arrive au bout d'une ligne
            if (((i + 1) % largeur) == 0) 
            {
                std::cout << std::endl;
            }

        }

    }
}

/// <summary>
/// affiche l'argument --help si il est contenu dans le tableau d'argument. il renvoie un booleen qui servira a arreter la fonction main
/// </summary>
/// <param name="argc"> int argc represente la taille du tableau tab donc le nombre d'arguments de main </param>
/// <param name="tab"> char* tab[] contient tout les arguments de main</param>
/// <returns> renvoie un booleen qui permet de savoir si l'argument --help a ete utilise </returns>
bool afficherhelp(int argc, char* tab[])
{
    // recherche de --help dans le tableau d'argument :
    bool vrai = false;
    for (size_t i = 0; i < argc; ++i)
    {
        std::string arg = tab[i];
        if (arg == "--help")
        {
            std::cout
                << "Usage :\n"
                << "pgm2txt [options]\n"
                << "Options :\n";
            std::cout << "--input fichier Spécifie le fichier image à convertir\n"
                << "Si ce paramètre n'est pas spécifié, le fichier est demandé via la console.\n"
                << "\n"
                << "--output fichier Spécifie le nom du fichier texte qui contiendra l'Ascii Art.\n"
                << "Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la console.\n";
            std::cout << "\n"
                << "--palette fichier Spécifie un fichier texte contenant la palette de couleur Ascii.\n"
                << "Chaque ligne du fichier contient un charactère en UTF-8, du plus\n"
                << "sombre au plus clair.\n";
            std::cout << "Si ce paramètre n'est pas spécifié, la palette par défaut est\n"
                << "\"W\", \"w\", \"l\", \"i\", \":\", \",\", \".\", \" \"\n"
                << "\n"
                << "--help\n"
                << "Affiche cette aide\n";
            vrai = true;
        }
    }
    return vrai;
}

