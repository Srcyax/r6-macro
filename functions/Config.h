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

	inline char name[20];
	inline bool isValidIndex(int index) {
		return index != -1;
	}
	static std::string directory = "C:\\Configs\\";
	inline std::string current = "default.json";
};