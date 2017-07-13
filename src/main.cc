#include <iostream>

#include "options/opt_parser.hh"

int main(int argc, char* argv[]) {
  std::cout << "hello, the build system seems to work." << std::endl;
  std::cout << "meme si le makefile a la racine semble ne servir a rien, laissez le, ca evite d'aller le chercher dans le dossier build." << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "oui, c'est la flemme qui parle" << std::endl;

  const std::string* option = options::parse_option(argc, argv);

  if (*option == "")
    return -1;

  if (!(*option).compare("help") || !(*option).compare("version"))
    // exit if help or version is asked
    return 0;

  if (!(*option).compare("dico"))
    std::cout << "dico" << std::endl;

  if ((option[1]).compare("freq"))
    std::cout << "freq" << std::endl;


  return 0;
}
