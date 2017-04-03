#include<stdlib.h>
#include<iostream>

#include"Translate_engine.hpp"


int main()
{
	//Init avec 'f' pour français
	Translate_engine toto('f');

	//Chargement de la phrase avec le code "sentence2" 
	std::string sentence = toto.get_sentence("sentence2");
	std::cout << sentence << std::endl;

	//Init de la map d'arguments
	std::map<std::string, std::string> arguments_test ;
	arguments_test["number"] = "22";
	arguments_test["object"] = "p51";

	
	//Remplissage de la phrase
	sentence = toto.fill_sentence(sentence, arguments_test);	
	std::cout << sentence << std::endl;
	
		
	system("PAUSE");
	return 0;
}