#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <cctype>
#include <locale>
#include <ctime>

std::vector<std::string> SplitStr(std::string str)
{
    std::vector<std::string> substrings;
    size_t startPos = 0, endPos;
    while ((endPos = str.find(' ', startPos)) != std::string::npos) {
        substrings.push_back(str.substr(startPos, endPos - startPos));
        startPos = endPos + 1;
    }

    substrings.push_back(str.substr(startPos));

    return substrings;
}


void SortingByDistanse(std::vector<std::vector<std::string>> lines) {
    std::vector<std::vector<std::string>> Hundred;
    std::vector<std::vector<std::string>> Thousand;
    std::vector<std::vector<std::string>> TenThousand;
    std::vector<std::vector<std::string>> OverAbove;

    for (int j = 1; j < lines.size(); j++) {
        for (int i = 0; i < lines.size() - 1; i++) {
            if (sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) > sqrt(pow(std::stod(lines[i+1][1]), 2) + pow(std::stod(lines[i+1][2]), 2))) {
                std::vector<std::string> x = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = x;
            }
        }
    }

    for (int i = 0; i < lines.size(); i++) {
        if (sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) <= 100){
            Hundred.push_back(lines[i]);
        }
        if (sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) > 100 && sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) <= 1000) {
            Thousand.push_back(lines[i]);
        }
        if (sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) > 1000 && sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) <= 10000) {
            TenThousand.push_back(lines[i]);
        }
        if (sqrt(pow(std::stod(lines[i][1]), 2) + pow(std::stod(lines[i][2]), 2)) > 10000) {
            OverAbove.push_back(lines[i]);
        }
    }
    
    std::ofstream output;
    output.open("SortingByDistanse.txt");
    if (output.is_open()) {
        output << "Group by 100" << std::endl;
        for (auto line : Hundred) {
            for (auto el : line) {
                output << el << " ";
            }
            output << std::endl;
        }
        output << std::endl << "Group by 1000" << std::endl;
        for (auto line : Thousand) {
            for (auto el : line) {
                output << el << " ";
            }
            output << std::endl;
        }
        output << std::endl << "Group by 10000" << std::endl;
        for (auto line : TenThousand) {
            for (auto el : line) {
                output << el << " ";
            }
            output << std::endl;
        }
        output << std::endl << "Group by OverAbove" << std::endl;
        for (auto line : OverAbove) {
            for (auto el : line) {
                output << el << " ";
            }
            output << std::endl;
        }
    }
    output.close();
}


void GroupByName(std::vector<std::vector<std::string>> lines) {
    std::locale russianLocale("ru_RU.UTF-8");
    std::multimap<char, std::string> Case;
    for (auto line : lines) {
        char first_char = std::tolower(line[0][0], russianLocale);

        std::string values;

        for (auto i = 0; i < line.size(); ++i) {
            values += line[i] + " ";
        }

        if (std::isalpha(first_char, russianLocale)) {
            Case.insert(std::pair<char, std::string>(first_char, values));
        }
        else {
            Case.insert(std::pair<char, std::string>('#', values));
        }

        
    }

    std::ofstream output;
    output.open("GroupByName.txt");
    if (output.is_open()) {
        output << "Group  - Value" << std::endl;
        for (auto& item : Case) {
            output << item.first << " - " << item.second << std::endl;
        }
    }
    output.close();
}


void SortingByTime(std::vector<std::vector<std::string>> lines) {
    std::time_t now = std::time(0);
    std::vector<std::vector<std::string>> Today;
    std::vector<std::vector<std::string>> Yesterday;
    std::vector<std::vector<std::string>> LastWeek;
    std::vector<std::vector<std::string>> ThisMonth;
    std::vector<std::vector<std::string>> ThisYear;
    std::vector<std::vector<std::string>> Earlier;

    for (int j = 1; j < lines.size(); j++) {
        for (int i = 0; i < lines.size() - 1; i++) {
            if (std::stod(lines[i][4]) > std::stod(lines[i+1][4])) {
                std::vector<std::string> x = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = x;
            }
        }
    }

    for (auto& line : lines) {
        std::time_t ObjectTime = std::stod(line[4]);
        std::time_t diffSeconds = now - ObjectTime;
        int temp = diffSeconds / (60 * 60 * 24);
        if (temp < 1) Today.push_back(line);
        if (temp > 1 && temp < 3) Yesterday.push_back(line);
        if (temp > 3 && temp < 8) LastWeek.push_back(line);
        if (temp > 8 && temp < 32) ThisMonth.push_back(line);
        if (temp > 32 && temp < 366) ThisYear.push_back(line);
        if (temp > 366) Earlier.push_back(line);
    }

    std::ofstream output;
    output.open("SortingByTime.txt");
    if (output.is_open()) {
        output << "Group by Yesterday\n";
        for (auto& line : Yesterday) {
            for (auto& el : line) {
                output << el << " ";
            }
        }
        output << "\nGroup by Last Week\n";
        for (auto& line : LastWeek) {
            for (auto& el : line) {
                output << el << " ";
            }
        }
        output << "\nGroup by This Month\n";
        for (auto& line : ThisMonth) {
            for (auto& el : line) {
                output << el << " ";
            }
        }
        output << "\nGroup by This Year\n";
        for (auto& line : ThisYear) {
            for (auto& el : line) {
                output << el << " ";
            }
        }
        output << "\nGroup by Earlier\n";
        for (auto& line : Earlier) {
            for (auto& el : line) {
                output << el << " ";
            }
        }
    }
    output.close();
}


void GroupByType(std::vector<std::vector<std::string>> lines, int N) 
{
    std::multimap<std::string, std::vector<std::vector<std::string>>> mp;
    std::vector<std::vector<std::string>> other;

    for (auto& line : lines) {
        auto it = mp.find(line[3]);
        if (it != mp.end()) {
            it->second.push_back(line);
        }
        else {
            mp.insert(std::make_pair(line[3], std::vector<std::vector<std::string>>{line}));
        }
    }

    for (auto it = mp.begin(); it != mp.end(); ++it) {
        auto& type = it->first;
        auto& group = it->second;

        if (group.size() < N) {
            other.insert(other.end(), group.begin(), group.end());
        }
    }

    std::ofstream output;
    output.open("GroupByType.txt");
    if (!output.is_open()) {
        return;
    }

    for (auto it = mp.begin(); it != mp.end(); ++it) {
        auto& type = it->first;
        auto& group = it->second;

        if (group.size() < N) {
            other.insert(other.end(), group.begin(), group.end());
        }
        else {
            output << "Group " << type << ":" << std::endl;
            for (auto& line : group) {
                for (auto& el : line) {
                    output << el << " ";
                }
                output << std::endl;
            }
            output << std::endl;
        }
    }

    if (!other.empty()) {
        output << "Other Group:" << std::endl;
        for (auto& line : other) {
            for (auto& el : line) {
                output << el << " ";
            }
            output << std::endl;
        }
    }
    output.close();
}


int main()
{
    //мы открываем файл и читаем в вектор все строки
    std::string line;
    std::vector<std::string> temp;
    std::locale newLocale("ru_RU.UTF-8");
    std::locale::global(newLocale);
    std::ifstream in("input.txt");
    in.imbue(newLocale);

    if (in.is_open()) {

        while (std::getline(in, line)) {
            temp.push_back(line);
            std::cout << line << std::endl;
        }
    }

    in.close();

    //после чего мы создаем двумерный вектор в котором будут храниться разбитые по пробелу строки
    std::vector<std::vector<std::string>> lines;
    //перебираем все строки в изначальном векторе и для каждой вызываем метод который ее разбивает и возвращает в качестве вектора
    for (auto var : temp) lines.push_back(SplitStr(var));
    SortingByDistanse(lines);
    GroupByName(lines);
    SortingByTime(lines);
    GroupByType(lines, 1);
}