#include <bits/stdc++.h>
std::map<std::string, std::string> diction;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    for (std::string temp; getline(std::cin, temp, '\n') && temp != "";) {
        std::string key = temp.substr(temp.find(' ') + 1);
        std::string val = temp.substr(0, temp.find(' '));
        diction[key] = val;
    }
    for (std::string check; std::cin >> check;) {
        std::map<std::string, std::string>::iterator result;
        result = diction.find(check);
        if (result != diction.end())
            std::cout << result->second.c_str() << std::endl;
        else
            std::cout << "eh" << std::endl;
    }
    return 0;
}