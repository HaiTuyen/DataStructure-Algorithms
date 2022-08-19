#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <math.h>
using namespace std;
#define STRING(num) #num

struct Node {
	string key;
	Node* pNext;
};

struct List {
	Node* pHead;
	Node* PTail;
};

List* initList();
bool isEmpty(List*& L);
Node* createNode(string data);
void addHead(List*& L, Node* N);
void pop(List*& L);

// Check the precedence of operator(Muc do uu tien cua cac toan tu)
int checPrecedence(char c);
string removeBracket(string s);
string removeMinus(string s);   // loai dau am de kiem tra
bool isValidPara(string s);
bool checkOperator(string s);
bool checkValidExpression(string s);

// Convert to postfix expressions
string infixToPostfix(string s);

// Evaluate
float applyOperator(float a, float b, char op);
string Evaluate(string s);

// File 
vector<string> readData(string input);
void exportData(vector<string> result, string output, int size);

// Driver code
int main(int argc, char* argv[])
{
	vector<string> list = readData(/*argv[1]*/"input.txt");
	vector<string> result;
	string temp = "";
	int size = atoi(/*argv[2]*/ "4");

	if (strcmp(/*argv[3]*/"-t", "-c") == 0) {
		cout << "Calculate!";
		for (int i = 0; i < size; i++)
		{
			temp = Evaluate(list[i]);
			result.push_back(temp);
		}
		exportData(result, /*argv[4]*/"output.txt", size);
	}

	if (strcmp(/*argv[3]*/"-t", "-t") == 0) {
		cout << "Convert action!";
		for (int i = 0; i < size; i++)
		{
			temp = infixToPostfix(list[i]);
			result.push_back(temp);
		}
		exportData(result, /*argv[4]*/"output.txt", size);
	}
	return 0;
}


List* initList()
{
	List* L = new List;
	L->pHead = NULL;
	L->PTail = NULL;
	return L;
}

bool isEmpty(List*& L)
{
	return L->pHead == NULL;
}

Node* createNode(string data)
{
	Node* nNode = new Node;
	if (nNode == NULL)
		return nNode;
	nNode->key = data;
	nNode->pNext = NULL;
	return nNode;
}

void addHead(List*& L, Node* N)
{
	if (L == NULL)
		return;
	if (L->pHead == NULL)
		L->pHead = L->PTail = N;
	else
	{
		N->pNext = L->pHead;
		L->pHead = N;
	}
}

void pop(List*& L)
{
	if (L->pHead == NULL)
		cout << "\nDanh sach rong.";
	else
	{
		Node* temp = L->pHead;
		L->pHead = temp->pNext;
		delete temp;
		return;
	}
}

// check the precedence of operator(Muc do uu tien cua cac toan tu)
int checPrecedence(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	return -1;
}

string removeBracket(string s)
{
	string a;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != ')' && s[i] != ']' && s[i] != '}' && s[i] != '(' && s[i] != '[' && s[i] != '{')
			a += s[i];
	}
	return a;
}

string removeMinus(string a)
{
	string newS = "";
	for (int i = 0; i < a.length(); i++)
	{
		if (checPrecedence(a[i]) != -1)
		{
			if (a[i] == '-')
			{
				if ((a[i + 1] == ' ' && a[i - 1] == ' ') || (a[i - 1] >= '0' && a[i - 1] <= '9'))
					newS += a[i];
			}
			else
				newS += a[i];
		}
		else
			newS += a[i];
	}
	return newS;
}

bool isValidPara(string s) {
	List* st;
	st = initList();    // khởi tạo Stack chứa các dấu ngoặc
	int n = s.size();
	// Bắt đầu duyệt chuỗi
	for (int i = 0; i < s.length(); i++)
	{
		// Nếu phần tử đang xét là các dấu mở ngoặc thì kiểm tra rồi thêm vào Stack
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
		{
			// Cần kiểm tra xem phần tử tiếp theo có phải là dấu đóng ngoặc không, nếu có thì hàm trả về giá trị false
			if (s[i + 1] == ')' || s[i + 1] == ']' || s[i + 1] == '}')
				return false;
			string temp;
			temp += s[i];
			addHead(st, createNode(temp));
		}
		// Trong trường hợp phần tử duyệt là các dấu đóng ngoặc, tiến hành kiểm tra đỉnh stack xem có phần tử mở ngoặc tương ứng
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
		{
			if (isEmpty(st))
				return false;
			else if (s[i] == ')' && st->pHead->key[0] != '(')
				return false;
			else if (s[i] == '}' && st->pHead->key[0] != '{')
				return false;
			else if (s[i] == ']' && st->pHead->key[0] != '[')
				return false;
			pop(st);

		}
	}
	// Nếu Stack rỗng, hàm trả về true
	return isEmpty(st);
}

bool checkOperator(string s)
{
	int countOperand = 0;
	string newS = removeMinus(s);
	int n = newS.length();
	for (int i = 0; i < newS.length(); i++)
	{
		if (checPrecedence(newS[i]) != -1)
			countOperand--;
		if (newS[i] >= '0' && newS[i] <= '9' && (newS[i + 1] == ' ' || newS[i + 1] == ')' || newS[i + 1] == ']' || newS[i + 1] == '}'))
			countOperand++;
	}
	// Khi duyệt đến cuối chuỗi, nếu phần tử phía trước nó là một toán hạng thì tăng biến đếm
	if (newS[n - 1] >= '0' && newS[n - 1] <= '9')
		countOperand++;
	return countOperand == 1;
}

bool checkValidExpression(string s)
{
	if (!isValidPara(s) || !checkOperator(s))
		return false;
	// nếu sau toán tử là dấu đóng mở ngoặc, hàm trả về false
	string b = removeMinus(s);
	for (int i = 0; i < s.length(); i++)
	{
		if (checPrecedence(s[i]) != -1 && (s[i + 1] == ')' || s[i + 1] == ']' || s[i + 1] == '}'))
			return false;
	}
	b = removeBracket(b);  // Loại bỏ ngoặc khỏi biểu thức
	stringstream ss(b);
	string temp = "";
	int count = 0;  // Biến đếm qua số lần duyệt
	bool checkDivide = false;   // biến kiểm tra có duyệt qua phép chia không, cho trường hợp phía sau dấu chia là số 0
	while (!ss.eof())
	{
		getline(ss, temp, ' ');
		if (count % 2 == 0)
		{
			// Nếu phần tử đầu của temp (lúc này nhận vào là số) không phải là số, biểu thức sai
			if (!(temp[0] >= '0' || temp[0] <= '9'))
				return false;
			else if (temp == "0" && checkDivide == true)
				return false;
			else
			{
				int countDot = 0;   // Đếm số lần xuất hiện của một dấu chấm trong chuỗi
				for (int i = 0; i < temp.length(); i++)
				{
					if (temp[i] == '.')
						countDot++;
					else if (!(temp[i] <= '9' && temp[i] >= '0'))
						return false;
				}
				//Nếu số lần xuất hiện của dấm chấm trong số quá 1 lần, biểu thức không hợp lệ
				if (countDot > 1)
					return false;
			}
			checkDivide = false;    // nếu hợp lệ gán lại giá trị false cho checkDivide
		}
		else if (count % 2 != 0)
		{
			if (checPrecedence(temp[0]) == -1 || (temp[0] >= '0' && temp[0] <= '9'))
				return false;
			else if (temp == "/")
				checkDivide = true;
		}
		count++;
	}
	return true;
}

string infixToPostfix(string s)
{
	if (!checkValidExpression(s))
		return "E";
	List* Stack;
	Stack = initList();
	string res;	// contain the final string
	for (int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if ((s[i] == '-' && s[i + 1] >= '0' && s[i + 1] <= '9') || (s[i] >= '0' && s[i] <= '9'))
		{
			res += s[i];
			while (s[i + 1] == '.' || (s[i + 1] >= '0' && s[i + 1] <= '9'))
			{
				res += s[i + 1];
				i++;
			}
			res += " ";
		}
		else if (c == '(' || c == '[' || c == '{')
		{
			string sTemp;
			sTemp += c;
			Node* temp = createNode(sTemp);
			addHead(Stack, temp);
		}
		// if ')' is scanned, we pop the stack and add it to the final string until '(' is encoutered 
		else if (c == ')' || c == ']' || c == '}')
		{
			while (Stack->pHead->key != "(" && Stack->pHead->key != "[" && Stack->pHead->key != "{")
			{
				res += Stack->pHead->key;
				res += " ";
				pop(Stack);
			}
			pop(Stack);	// delete '('
		}
		else if (c != ' ')	// if we scan an opearator
		{
			while (!isEmpty(Stack) && checPrecedence(s[i]) <= checPrecedence(Stack->pHead->key[0]))
			{
				if (c == '^' && Stack->pHead->key[0] == '^')
					break;
				else
				{
					res += Stack->pHead->key;
					res += " ";
					pop(Stack);
				}
			}
			string temp;
			temp += c;
			addHead(Stack, createNode(temp));
		}
	}
	while (!isEmpty(Stack))
	{
		res += Stack->pHead->key;
		res += " ";
		pop(Stack);
	}

	// show result
	return res;
}

// Evaluate
float applyOperator(float a, float b, char op)
{
	switch (op)
	{
	case '^':
		return pow(a, b);
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		break;
	}
	return 0;
}

string Evaluate(string s)
{
	if (!checkValidExpression(s))
		return "E";
	int i;
	List* value = initList();	// conatain value
	List* ops = initList();	// contain operator
	for (i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			continue;
		else if (s[i] == '(' || s[i] == '[' || s[i] == '{')
		{
			string temp;
			temp += s[i];
			addHead(ops, createNode(temp));
		}
		else if ((s[i] == '-' && s[i + 1] >= '0' && s[i + 1] <= '9') || (s[i] >= '0' && s[i] <= '9'))
		{
			string temp = "";
			temp += s[i];
			while (s[i + 1] == '.' || (s[i + 1] >= '0' && s[i + 1] <= '9'))
			{
				temp += s[i + 1];
				i++;
			}
			addHead(value, createNode(temp));
		}
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
		{
			while (!isEmpty(ops) && ops->pHead->key != "(" && ops->pHead->key != "[" && ops->pHead->key != "{")
			{
				float val2 = stof(value->pHead->key);
				pop(value);
				float val1 = stof(value->pHead->key);
				pop(value);
				char op = ops->pHead->key[0];
				pop(ops);
				float exVal = applyOperator(val1, val2, op);

				//After apply operator, we convert it from float to string then add to list conatains value
				string fNumber(to_string(exVal));
				addHead(value, createNode(fNumber));
			}
			pop(ops);
		}
		else
		{
			while (!isEmpty(ops) && checPrecedence(ops->pHead->key[0]) >= checPrecedence(s[i]))
			{
				float val2 = stof(value->pHead->key);
				pop(value);
				float val1 = stof(value->pHead->key);
				pop(value);

				char op = ops->pHead->key[0];
				pop(ops);
				float exVal = applyOperator(val1, val2, op);

				string fNumber(to_string(exVal));
				addHead(value, createNode(fNumber));
			}
			string temp;
			temp += s[i];
			addHead(ops, createNode(temp));
		}
	}

	while (!isEmpty(ops))
	{
		float val2 = stof(value->pHead->key);
		pop(value);
		float val1 = stof(value->pHead->key);
		pop(value);

		char op = ops->pHead->key[0];
		pop(ops);
		float exVal = applyOperator(val1, val2, op);

		string fNumber(to_string(exVal));
		addHead(value, createNode(fNumber));
	}

	return value->pHead->key;
}

// File 
vector<string> readData(string input)
{
	vector<string> dataList;
	ifstream ifs;
	ifs.open(input);
	if (!ifs.is_open()) {
		exit(0);
	}
	string line = "";
	while (!ifs.eof()) {
		getline(ifs, line);
		dataList.push_back(line);
	}
	ifs.close();
	return dataList;
}

void exportData(vector<string> result, string output, int size)
{
	ofstream ofs;
	ofs.open(output);
	if (!ofs.is_open())
	{
		exit(0);
	}
	for (int i = 0; i < size; i++)
	{
		if (result[i] == "E")
			ofs << result[i] << endl;
		else
		{
			float f = stof(result[i]);
			ofs << fixed << setprecision(2) << f << endl;
		}
	}
	ofs.close();
	return;
}