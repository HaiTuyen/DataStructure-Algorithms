#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

vector<Company> ReadCompanyList(string file_name)
{
    vector<Company> list;
    Company comp;
    ifstream ifs;
    ifs.open(file_name);
    string temp, name, profit_tax, address;
    getline(ifs, temp);
    while (!ifs.eof())
    {
        getline(ifs, temp);
        stringstream ss(temp);
        getline(ss, name, '|');
        getline(ss, profit_tax, '|');
        getline(ss, address, '|');

        comp.name = name;
        comp.profit_tax = profit_tax;
        comp.address = address;
        list.push_back(comp);
    }
    ifs.close();
    return list;
}

long long hashCalculate(int p, int i, int m)
{
    long long res = 1;
    for (int j = 0; j < i; j++)
    {
        res *= p;
        res = res % m;
    }
    return res;
}

long long hashString(string company_name)
{
    int len = company_name.size() > 20 ? 20 : company_name.size();
    int begin = company_name.size() > 20 ? company_name.size() - 20 : 0;
    long long m = pow(10, 9) + 9;
    long long hashValue = 0;
    for (int i = begin; i < (begin + len); i++)
    {
        hashValue += int(company_name[i]) * hashCalculate(31, i - begin, m);
        hashValue = hashValue % m;
    }
    return hashValue;
}

Company* CreateHashTable(vector<Company> list_company)
{
    Company* hashTable = new Company[2000];
    for (int i = 0; i < list_company.size(); i++)
    {
        hashTable[i] = {"", "", ""};
    }

    int hashValue;
    for (int i = 0; i < list_company.size(); i++)
    {
        hashValue = hashString(hashTable[i].name);
        if (hashTable[hashValue % 2000].name == "")
        {
            hashTable[hashValue % 2000] = {list_company[i].name, list_company[i].profit_tax, list_company[i].address};
        }
        else 
        {
            int temp = hashValue % 2000 + 1;
            while (hashTable[temp].name != "")
            {
                temp = (temp + 1) % 2000;
            }
            hashTable[temp] = {list_company[i].name, list_company[i].profit_tax, list_company[i].address};
        }
    }

    return hashTable;
}

void Insert(Company* hash_table, Company company)
{
	int hashVal = hashString(company.name);
    if (hash_table[hashVal % 2000].name == "")
    {
        hash_table[hashVal % 2000] = {company.name, company.profit_tax, company.address};
    }
    else 
    {
        int temp = hashVal % 2000 + 1;
        while (hash_table[temp].name != "")
        {
            temp = (temp + 1) % 2000;
        }
        hash_table[hashVal % 2000] = {company.name, company.profit_tax, company.address};
    }
}

Company* Search(Company* hash_table, string company_name)
{
    int hashVal = hashString(company_name);
    while (hash_table[hashVal % 2000].name != company_name)
    {
        if (hash_table[hashVal % 2000].name == "")
        {
            return NULL;
        }
        hashVal = (hashVal + 1) % 2000;
    }
    return &hash_table[hashVal % 2000];
}

int main()
{
    vector<Company> list = ReadCompanyList("MST.txt");
    int hashValue0 = hashString(list[0].name);
    int hashValue1 = hashString(list[1].name);
    int hashValue2 = hashString(list[2].name);
    return 0;
}