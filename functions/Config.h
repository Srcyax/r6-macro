#include "..\nlohmann\json.hpp"
#include <fstream>
#include <cstdio>
#include "../Header Files/globals.hh"

using json = nlohmann::json;
namespace config
{
	void Create();
	void Remove(const char* name);
	void Load(std::string name);
	void Save(std::string name);   
};