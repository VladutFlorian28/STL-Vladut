#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    vector<pair<string, string>> problems;
    vector<pair<string, string>> doctors;




    inFile >> no_problems;
    for (int i = 0; i < no_problems; ++i) {
        string name, speciality;
        inFile >> name >> speciality;
        problems.emplace_back(name, speciality);
    }


    inFile >> no_doctors;
    for (int i = 0; i < no_doctors; ++i) {
        string name, speciality;
        inFile >> name >> speciality;
        doctors.emplace_back(name, speciality);
    }


    unordered_map<string, bool> problem_solved;
    for (const auto& problem : problems) {
        problem_solved[problem.first] = false;
    }


    vector<pair<string, string>> assignments;

    for (const auto& doctor : doctors) {
        auto it = find_if(problems.begin(), problems.end(), [&](const pair<string, string>& problem) {
            return !problem_solved[problem.first] && problem.second == doctor.second;
            });

        if (it != problems.end()) {
            assignments.emplace_back(doctor.first, it->first);
            problem_solved[it->first] = true;
        }
    }


    for (const auto& assignment : assignments) {
        cout << assignment.first << " " << assignment.second << endl;
    }

    return 0;
}
