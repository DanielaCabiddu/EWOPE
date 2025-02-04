#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <string>
#include <vector>

bool findDeps_from_JSON (const std::string &JSONfilename);

std::vector<std::string> getDeps_from_JSON  (const std::string &JSONfilename);
std::vector<std::string> getCom_from_JSON   (const std::string &JSONfilename);

void getDeps_from_JSON_extended (const std::string &JSONfilename, std::vector<std::string> &deps, std::vector<std::string> &commands);


#ifndef STATIC_EWOPE
#include "dependencies.cpp"
#endif

#endif // DEPENDENCIES_H
