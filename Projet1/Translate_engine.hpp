#ifndef TRANSLATE_ENGINE
#define TRANSLATE_ENGINE

#include<string>
#include<map>
#include"tinyxml/tinyxml.h"
#include<iostream>

class Translate_engine
{
	/*Class witch translate arguments and sentences 
	  String of sentences and arguments are load from xml files
	  Sentences and arguments must match with an ID to defined in the spec*/
public:
	Translate_engine();
	Translate_engine(char language);
	void get_args(std::map<std::string, std::string> &args);
	std::string get_sentence(const std::string  &id_s);
	std::string fill_sentence(const std::string &sentence, const std::map<std::string, std::string> &args);
	
private:
	char language;
	TiXmlDocument xmlfile;
	
	
	
};

#endif // !TRANSLATE_ENGINE