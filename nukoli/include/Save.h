#pragma once
#include<unordered_map>
#include<string>
#include <fstream>
enum class SaveType {
    INT,
    FLOAT,
    STRING,
    BOOL,
    CHAR
};
class SaveEntry {
public:
    SaveType type;
    std::string data;
};
extern std::unordered_map<std::string,SaveEntry> saveData;

void SaveValue(int value,std::string name);
void SaveValue(float value,std::string name);
void SaveValue(std::string value,std::string name);
void SaveValue(bool value,std::string name);
void SaveValue(char value,std::string name);
void SaveDataFile();

int GetIntValue(std::string name);
void LoadDataFile();