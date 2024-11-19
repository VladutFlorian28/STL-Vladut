#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Problem {
    string name;
    string speciality;
    int duration;
};

struct Doctor {
    string name;
    string speciality;
    int available_at = 9; 
};

int main() {
    ifstream inFile("input4_bonus.txt");

    if (!inFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int no_problems, no_doctors;
    vector<Problem> problems;
    vector<Doctor> doctors;

    inFile >> no_problems;
    for (int i = 0; i < no_problems; ++i) {
        string name, speciality;
        int duration;
        inFile >> name >> speciality >> duration;
        problems.push_back({ name, speciality, duration });
    }

    inFile >> no_doctors;
    for (int i = 0; i < no_doctors; ++i) {
        string name, speciality;
        inFile >> name >> speciality;
        doctors.push_back({ name, speciality });
    }

    unordered_map<string, bool> problem_solved;
    for (const auto& problem : problems) {
        problem_solved[problem.name] = false;
    }

    vector<tuple<string, int, vector<string>>> assignments; 

    for (auto& doctor : doctors) {
        vector<string> assigned_problems;
        int total_duration = 0;

        for (auto& problem : problems) {
            if (!problem_solved[problem.name] &&
                problem.speciality == doctor.speciality &&
                doctor.available_at + problem.duration <= 17) { 

                assigned_problems.push_back(problem.name);
                doctor.available_at += problem.duration; 
                total_duration += problem.duration;
                problem_solved[problem.name] = true;
            }
        }

        if (!assigned_problems.empty()) {
            assignments.emplace_back(doctor.name, assigned_problems.size(), assigned_problems);
        }
    }

   
    if (assignments.empty()) {
        cout << "No assignments could be made." << endl;
    }
    else {
        for (const auto& assignment : assignments) {
            cout << get<0>(assignment) << " " << get<1>(assignment);
            for (const auto& problem : get<2>(assignment)) {
                cout << " " << problem;
            }
            cout << endl;
        }
    }

    return 0;
}
