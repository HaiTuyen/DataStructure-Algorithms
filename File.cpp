#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Examinee
{
	string id;
	float grade[11];
};

//1. Read the information of one candidate:
Examinee readExaminee(string line_info) {
	Examinee candidate;
	stringstream ss(line_info);
	getline(ss, candidate.id, ',');
	string temp = "";
	getline(ss, temp, ',');
	for (int i = 0; i < 11; i++) {
		getline(ss, temp, ',');
		if (temp == "") {
			candidate.grade[i] = 0;
		}
		else {
			candidate.grade[i] = stof(temp);
		}
	}
	candidate.grade[8] = candidate.grade[2] + candidate.grade[3] + candidate.grade[4];
	candidate.grade[9] = candidate.grade[5] + candidate.grade[6] + candidate.grade[7];
	return candidate;
}

//2. Read the information of a list of candidates:
vector<Examinee> readExamineeList(string file_name) {
	vector<Examinee> list;
	ifstream ifs;
	ifs.open(file_name);
	if (!ifs.is_open()) {
		cout << "Khong mo duoc file";
		return list;
	}

	string info_line = "";
	getline(ifs, info_line);
	while (!ifs.eof()) {
		getline(ifs, info_line);
		Examinee temp = readExaminee(info_line);
		list.push_back(temp);
	}

	ifs.close();
	return list;
}

//3. Write the total score of candidates to file:
void writeTotal(vector<Examinee> examinee_list, string out_file_name) {
	ofstream ofs;
	ofs.open(out_file_name);
	if (!ofs.is_open()) {
		cout << "Khong mo duoc file";
		return;
	}

	float sum = 0;
	for (int i = 0; i < examinee_list.size(); i++) {
		ofs << examinee_list[i].id << " ";
		sum = examinee_list[i].grade[0] + examinee_list[i].grade[1] + examinee_list[i].grade[8] 
			+ examinee_list[i].grade[9] + examinee_list[i].grade[10];
		ofs << sum << endl;
	}
	ofs.close();
}

void printExaminee(Examinee candidate) {
	cout << "ID: " << candidate.id << ",";
	for (int i = 0; i < 11; i++) {
		/*switch (i) {
		case 0: cout << "math: " << candidate.grade[i] << endl; break;
		case 1: cout << "literature: " << candidate.grade[i] << endl; break;
		case 2: cout << "physic: " << candidate.grade[i] << endl; break;
		case 3: cout << "chemistry: " << candidate.grade[i] << endl; break;
		case 4: cout << "biology: " << candidate.grade[i] << endl; break;
		case 5: cout << "history: " << candidate.grade[i] << endl; break;
		case 6: cout << "geography: " << candidate.grade[i] << endl; break;
		case 7: cout << "civic_education: " << candidate.grade[i] << endl; break;
		case 8: cout << "natural_science: " << candidate.grade[i] << endl; break;
		case 9: cout << "social_science: " << candidate.grade[i] << endl; break;
		case 10: cout << "foreign_language: " << candidate.grade[i] << endl; break;
		}*/
		cout << candidate.grade[i] << ",";
	}
	cout << endl;
}

void printExamineeList(vector<Examinee> list) {
	for (int i = 0; i < list.size(); i++) {
		printExaminee(list[i]);
	}
}

int main() {
	string file_name = "data.txt";
	vector<Examinee> list = readExamineeList(file_name);
	writeTotal(list, "result.txt");
	return 0;
}