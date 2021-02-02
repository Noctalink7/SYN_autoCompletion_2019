/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** autoCompletion
*/

#include "autoCompletion.hpp"
#include "Exception.hpp"
#include <algorithm>
#include <utility>
#include <sys/stat.h>

AutoComp::AutoComp()
{
    this->checkProp = false;
}

std::vector<std::string> AutoComp::split(std::string str)
{
    size_t start;
    size_t end = 0;
    const char delim = ' ';
    std::vector<std::string> tmp;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        tmp.push_back(str.substr(start, end - start));
    }
    return tmp;
}

long AutoComp::GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);

    return rc == 0 ? stat_buf.st_size : -1;
}

int AutoComp::ProcessFile(std::string filename)
{
    std::ifstream file;
    std::string line;
    std::regex regex("^([\\w\\s]*), ([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+)$");
    std::smatch matches;
    bool error = false;

    file.open(filename.c_str());
    if (file.is_open() == false)
        throw Exception("Error: File doesn't exist");
    if (GetFileSize(filename) == 0)
        throw Exception("Error: File empty");
    while(std::getline(file, line)) {
        if (regex_search(line, matches, regex)) {
            Address *address = new Address(split(matches[1].str()), atoi(matches[2].str().c_str()), matches[3].str(), split(matches[4].str()), line);
            list.push_back(*address);
        } else {
            std::cerr << line << std::endl;
            error = true;
        }        
    }
    if (error == true)
        throw Exception("Unknown address");
    return 0;
}

bool sortByVal(const std::pair<char, int> &a, const std::pair<char, int> &b) 
{ 
    return (b.second < a.second); 
}

bool AutoComp::fivemost(int i)
{
    std::map<char, int> map;
    std::vector<std::pair<char, int>> vec;
    std::map<char, int> :: iterator it;
    char tmp;

    if (list.size() == 1) {
        checkProp = true;
        return true;
    }
    for(auto& addr: list) {
        for(auto& city : addr.getCity()) {
            if (city.size() <= (size_t)i) {
                checkProp = true;
                return true;
            }
            tmp = std::tolower(city[i]);
            if (map.find(tmp) != map.end())
                map[tmp] += 1;
            else
                map[tmp] = 1;
        }
    }
    if (map.size() == 1) {
        checker += std::toupper(map.begin()->first);
        return false;
    }
    for (it=map.begin(); it!=map.end(); it++)
        vec.push_back(std::make_pair(it->first, it->second));
    std::sort(vec.begin(), vec.end(), sortByVal);
    for (size_t i = 0; i < vec.size() && i < 5; i++) {
        std::cout << "{" << checker  << vec[i].first << "}";
        if (i < vec.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
    return true;
}

void AutoComp::fivemostAddr()
{
    std::map<char, int> map;
    std::vector<std::pair<char, int>> vec;
    std::map<char, int> :: iterator it;
    char tmp;

    if (list.size() == 1)
        return;
    for(auto& addr: list) {
	for(auto& name : addr.getName()) {
            tmp = std::tolower(name[0]);
            if (map.find(tmp) != map.end())
                map[tmp] += 1;
            else
                map[tmp] = 1;
        }
    }
    for (it=map.begin(); it!=map.end(); it++)
	vec.push_back(std::make_pair(it->first, it->second));
    std::sort(vec.begin(), vec.end(), sortByVal);
    for (size_t i = 0; i < vec.size() && i < 5; i++) {
        std::cout << "{" << printVec(upCity) << ", " << vec[i].first << "}";
        if (i < vec.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
}

std::string AutoComp::toLower(std::string str)
{
    std::string tmp;

    for (size_t i = 0; i != str.size(); i++)
        tmp += std::tolower(str[i]);
    return tmp;
}

std::string AutoComp::toUpper(std::string str)
{
    std::string tmp;

    for (size_t i = 0; i != str.size(); i++)
        tmp += std::toupper(str[i]);
    return tmp;
}

std::vector<std::string> AutoComp::VecUpper(std::vector<std::string> vec)
{
    std::vector<std::string> tmp;

    for (auto& str : vec)
        tmp.push_back(toUpper(str));
    return tmp;
}

bool AutoComp::checkCity(std::vector<Address>::iterator it)
{
    bool tmp = true;
    bool check = false;
    size_t i = 0;

    for (auto& city : it->getCity()) {
        tmp = true;
        if (checker.size() > city.size()) {
            continue;
        }
//        std::cout << checker << " " << city << std::endl;
        if (toLower(checker) == toLower(city)) { //Problème avec plusieurs mot dans la ville
            upCity = VecUpper(it->getCity());
            return true;
        } //else ?
        for (i = 0; i != checker.size(); i++) {
            //           std::cout << checker[i] << " " << city[i] << std::endl;
            if (std::tolower(checker[i]) != std::tolower(city[i])) {
                tmp = false;
                break;
            }
        }
        if (tmp == true) {
            next = std::tolower(city[i]);
//            std::cout << next << "next" << std::endl;
            if (prop.find(next[0]) != prop.end())
                prop[next[0]] += 1;
            else
                prop[next[0]] = 1;
            check = true;
//            return true;
        }
    }
    return check;
}

bool AutoComp::searchCity(std::string input)
{
    std::vector<std::string> tmp;
    std::vector<std::pair<char, int>> vec;

    prop.clear();    
    checker = checker + input; //tolower input
    for (std::vector<Address>::iterator it = list.begin() ; it != list.end(); it++)
        if (checkCity(it) == false) {
            list.erase(it);
            it--;
        }
//    std::cout << prop.size() << " map size" << std::endl;
    if (prop.size() == 1) {
//        std::cout << next << std::endl;
        prop.clear();
        if (searchCity(next) == true)
            return true;
        else
            return false;
    }
    if (list.size() == 1)
        return true;
    if (prop.size() == 0 && list.size() == 0)
        throw Exception("Unknown address");
    if (prop.size() == 0 && list.size() != 0) {
//        std::cout << "city was found" << std::endl;
        return true;
    }
    //print here test
    for (std::map<char, int>::iterator it = prop.begin(); it != prop.end(); it++)
        vec.push_back(std::make_pair(it->first, it->second));
    std::sort(vec.begin(), vec.end(), sortByVal);
    std::transform(checker.begin(), checker.end(),checker.begin(), ::toupper);
    for (size_t i = 0; i < vec.size() && i < 5; i++) {
        std::cout << "{" << checker + vec[i].first << "}";
        if (i < vec.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
    return false;
}

bool AutoComp::checkStreet(std::vector<Address>::iterator it)
{
    bool tmp = true;
    bool check = false;
    size_t i = 0;

    for (auto& street : it->getName()) {
        tmp = true;
        if (checker.size() > street.size()) {
            continue;
        }
        if (toLower(checker) == toLower(street)) {
            upName = VecUpper(it->getName());
            return true;
        } //else ?
        for (i = 0; i != checker.size(); i++) {
            if (std::tolower(checker[i]) != std::tolower(street[i])) {
                tmp = false;
                break;
            }
        }
        if (tmp == true) {
            next = std::tolower(street[i]);
//            std::cout << next << "next" << std::endl;
            if (prop.find(next[0]) != prop.end())
                prop[next[0]] += 1;
            else
                prop[next[0]] = 1;
            check = true;
//            return true;                                                      
        }
    }
    return check;
}

bool AutoComp::searchStreet(std::string input) //problème "de, des"
{
    std::vector<std::string> tmp;
    std::vector<std::pair<char, int>> vec;

    prop.clear();
    checker = checker + input;
    for (std::vector<Address>::iterator it = list.begin() ; it != list.end(); it++)
        if (checkStreet(it) == false) {
//            std::cout << it->getAddr() << std::endl;
            list.erase(it);
            it--;
        }
    if (prop.size() == 1) {
        prop.clear();
        if (searchStreet(next) == true)
            return true;
        else
            return false;
    }
    if (list.size() == 1)
        return true;
    if (prop.size() == 0 && list.size() == 0)
        throw Exception("Unknown address");
    if (prop.size() == 0 && list.size() != 0) {
        return true;
    }
    for (std::map<char, int>::iterator it = prop.begin(); it != prop.end(); it++)
        vec.push_back(std::make_pair(it->first, it->second));
    std::sort(vec.begin(), vec.end(), sortByVal);
    std::transform(checker.begin(), checker.end(),checker.begin(), ::toupper);
    for (size_t i = 0; i < vec.size() && i < 5; i++) {
        std::cout << "{" << printVec(upCity) << ", " << checker + vec[i].first << "}";
        if (i < vec.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
    return false;
}

std::string AutoComp::printVec(std::vector<std::string> vec)
{
    std::string tmp;
    size_t size = 0;

    for (auto& str : vec) {
        tmp += str;
        if (size < vec.size() - 1)
            tmp += " ";
        size++;
    }
    return tmp;
}

std::vector<std::string> AutoComp::getupCity()
{
    return this->upCity;
}

std::vector<Address> AutoComp::getList()
{
    return this->list;
}

void AutoComp::ResetChecker()
{
    this->checker = "";
}

bool AutoComp::getCheck()
{
    return this->checkProp;
}
