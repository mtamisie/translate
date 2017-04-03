#include"Translate_engine.hpp"

Translate_engine::Translate_engine() :language('f'), xmlfile("XMLFile.xml")
{	 
	/*Load default file*/
	if (!xmlfile.LoadFile()) {
		std::cout << "loading error" << std::endl;
		std::cout << "error #" << xmlfile.ErrorId() << " : " << xmlfile.ErrorDesc() << std::endl;		
	}
}

Translate_engine::Translate_engine(char lg ): language(lg), xmlfile()
{
	/*Load the wanted file*/
	switch (lg)
	{
	case 'f': xmlfile = "XMLFile.xml";
		if (!xmlfile.LoadFile())
		{
			std::cout << "loading error" << std::endl;
			std::cout << "error #" << xmlfile.ErrorId() << " : " << xmlfile.ErrorDesc() << std::endl;
		}
		break;

	case 'e': xmlfile = "XMLFile.xml";
		if (!xmlfile.LoadFile())
		{
			std::cout << "loading error" << std::endl;
			std::cout << "error #" << xmlfile.ErrorId() << " : " << xmlfile.ErrorDesc() << std::endl;
		}
		break;
	}	
}

std::string Translate_engine::get_sentence(std::string const &id_s)
{
	std::string sentence; //String where the sentence will be built

	//search hole sentence in xml
	TiXmlHandle hdl(&xmlfile);
	TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement("sentences").FirstChildElement(id_s.c_str()).Element();
	if (!elem) {
		std::cout << "there is no node" << std::endl;
	}

	return elem->Attribute("val");
	
}

std::string Translate_engine::fill_sentence(const std::string &sentence,  const std::map<std::string, std::string> &args)
{
	//begin read hole sentence

	 //store the hole sentence

	std::string tamp;
	std::string::const_iterator it(sentence.begin());
	TiXmlHandle hdl(&xmlfile);
	TiXmlElement *elem;

	for (it = sentence.begin(); it != sentence.end(); it++)
	{
		if (*it == '{')
		{
			it++;
			std::string arg;

			while (*it != '}')
			{
				arg += *it;
				it++;
			}
			
			elem = hdl.FirstChildElement().FirstChildElement("objects").FirstChildElement(args.at(arg).c_str()).Element();
			if (!elem) 
			{
				if (arg == "number")
				{
					tamp += args.at(arg);
					it++;					
				}					
				else
				{
					std::cout << "there is no node" << std::endl;
					return"";
				}				
			}
			else
			{
				tamp += elem->Attribute("val");
				it++;
			}
			
			
		}

		//If the '}' symbole is at the end of the string  
		if ((it != sentence.end()) && (*it!='{'))
			tamp += *it;
		else if (it == sentence.end())
			break;
	}
	return tamp;
}


void Translate_engine::get_args(std::map<std::string, std::string> &args)
{
	
	TiXmlHandle hdl(&xmlfile);
	std::map<std::string, std::string>::iterator it(args.begin());

	for (it; it != args.begin(); it++)
	{
		args[it->first] = hdl.FirstChildElement().FirstChildElement("objects").FirstChildElement(it->first.c_str()).Element()->Attribute("val");
	}	

}