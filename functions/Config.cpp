#include "Config.h"

void config::Create() {
    json data;
    data["x"] = 0.f;
    data["y"] = 0.f;
    data["time"] = 0.f;

    std::fstream file(globals.configDirectory + globals.configName + ".json", std::ios::out);

    file << data.dump();
    file.close();
}

void config::Remove(const char* name) {
    std::remove((globals.configDirectory + name).c_str());
}

void config::Load(std::string name) {
    std::ifstream file(globals.configDirectory + name, std::ios::out);
    json data;
    file >> data;
    file.close();

    mouse::x = data["x"];
    mouse::y = data["y"];
    mouse::time = data["time"];
}

void config::Save(std::string name) {
    json data;
    data["x"] = mouse::x;
    data["y"] = mouse::y;
    data["time"] = mouse::time;

    std::ofstream file(globals.configDirectory + name, std::ios::out);
    file << data.dump();
    file.close();
}