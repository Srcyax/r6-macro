#include "Config.h"

void config::Create() {
    json data;
    data["x"] = 0.f;
    data["y"] = 0.f;
    data["time"] = 0.f;
    data["active"] = false;
    data["key"] = 0;

    std::fstream file(config::directory + config::name + ".json", std::ios::out);

    file << data.dump();
    file.close();
}

void config::Remove(const char* name) {
    std::remove((config::directory + name).c_str());
}

void config::Load(std::string name) {
    std::ifstream file(config::directory + name, std::ios::out);
    json data;
    file >> data;
    file.close();

    mouse::x = data["x"];
    mouse::y = data["y"];
    mouse::time = data["time"];
    mouse::active = data["active"];
    mouse::key = data["key"];
}

void config::Save(std::string name) {
    json data;
    data["x"] = mouse::x;
    data["y"] = mouse::y;
    data["time"] = mouse::time;
    data["active"] = mouse::active;
    data["key"] = mouse::key;

    std::ofstream file(config::directory + name, std::ios::out);
    file << data.dump();
    file.close();
}