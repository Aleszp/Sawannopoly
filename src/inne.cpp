//Standardowe nagłówki C/C++
#include <string>
#include <cstring>

//Nagłówki z katalogu programu
#include "inne.hpp"

std::string wytnij(char* zrodlo)
{
	std::string tmpString(zrodlo);
	size_t przesuniecie=tmpString.find(",");
	
	std::string outString(tmpString,0,przesuniecie);
	tmpString=tmpString.substr(przesuniecie+1);
	
	strcpy(zrodlo, tmpString.c_str());
	return outString;
}
