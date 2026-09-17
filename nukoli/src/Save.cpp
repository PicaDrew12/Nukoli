#include "Save.h"

#include <map>

#include "Debug.h"
//DRAFT, WILL OPTIMIZE LATER
std::unordered_map<std::string,SaveEntry> saveData;


void SaveValue(int value,std::string name) {
    SaveEntry entry;
    entry.type = SaveType::INT;
    entry.data = std::to_string(value);
    saveData[name] = entry;
}
void SaveValue(float value, std::string name) {
    SaveEntry entry;
    entry.type = SaveType::FLOAT;
    entry.data = std::to_string(value);
    saveData[name] = entry;
}

void SaveValue(std::string value, std::string name) {
    SaveEntry entry;
    entry.type = SaveType::STRING;
    entry.data = value;
    saveData[name] = entry;
}
void SaveValue(bool value, std::string name) {
    SaveEntry entry;
    entry.type = SaveType::BOOL;
    entry.data = value ? "true" : "false";
    saveData[name] = entry;
}

void SaveValue(char value, std::string name) {
    SaveEntry entry;
    entry.type = SaveType::CHAR;
    entry.data = std::string(1, value);
    saveData[name] = entry;
}


std::string typeToString(SaveType type) {
    switch (type) {
        case SaveType::INT:    return "INT";
        case SaveType::FLOAT:  return "FLOAT";
        case SaveType::STRING: return "STRING";
        case SaveType::BOOL:   return "BOOL";
        case SaveType::CHAR:   return "CHAR";
        default:               return "UNKNOWN";
    }
}

SaveType stringToType(const std::string& str) {
    if (str == "INT")    return SaveType::INT;
    if (str == "FLOAT")  return SaveType::FLOAT;
    if (str == "STRING") return SaveType::STRING;
    if (str == "BOOL")   return SaveType::BOOL;
    if (str == "CHAR")   return SaveType::CHAR;


    Debug::Error(("Unknown SaveType: " + str));
}


void SaveDataFile() {

    std::ofstream saveFile("saveFile.sf");for (auto element : saveData) {
        if (element.second.type == SaveType::STRING) {
            saveFile << "STRING "
                     << element.first
                     << " # "
                     << element.second.data
                     << " #\n";
        } else {
            saveFile << typeToString(element.second.type)
                     << " "
                     << element.first
                     << " "
                     << element.second.data
                     << '\n';
        }
    }
}

void LoadDataFile() {
    std::string name = "saveFile.sf";
    std::ifstream f(name.c_str());
    if (!f.good()) {
        std::ofstream saveFile;
        saveFile.open("saveFile.sf");
    }
    std::ifstream saveFile("saveFile.sf");
    std::string type;
    while (saveFile>>type) {
        if (type == "INT") {
            std::string name;
            saveFile>>name;
            int value;
            saveFile>>value;
            SaveValue(value,name);

        }
        if (type == "FLOAT") {
            std::string name;
            saveFile>>name;
            float value;
            saveFile>>value;
            SaveValue(value,name);

        }if (type == "BOOL") {
            std::string name;
            saveFile>>name;
            std::string value;
            saveFile>>value;
            if (value =="true") {
                SaveValue(true,name);
            }
            if (value =="false") {
                SaveValue(false,name);
            }


        }

        if (type=="CHAR") {
            std::string name;
            saveFile>>name;
            char value;
            saveFile>>value;
            SaveValue(value,name);
        }

        if (type == "STRING") {
            std::string name;
            saveFile>>name;
            std::string text;
            std::string fullString="";
            saveFile>>text;
            if (text =="#") {
                while (saveFile>>text) {
                    if (text == "#") {
                        break;
                    }else {
                        fullString += text+" ";
                    }
                }
                SaveValue(fullString,name);
            }else {
                Debug::Error("STRING WRONG FORMAT SAVE FILE");
            }
        }
    }
}

//Loaders

SaveEntry& FindSaveEntry(const std::string& name) {
    for (auto& entry: saveData) {
        if (entry.first == name) {
            return entry.second;
        }
    }
    Debug::Error("No save variable with name:'"+name+"'");
}

int LoadDataInt(const std::string& name) {
    return std::stoi(FindSaveEntry(name).data);
}

float LoadDataFloat(const std::string& name) {
    return std::stof(FindSaveEntry(name).data);
}

char LoadDataChar(const std::string& name) {
    return FindSaveEntry(name).data[0];
}

std::string& LoadDataString(const std::string& name) {
    return FindSaveEntry(name).data;
}

bool LoadDataBool(const std::string& name) {
    return FindSaveEntry(name).data == "true";
}