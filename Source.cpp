#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

bool check_reserved(string s, string ar[])
{
	for (int i = 0; i < 8; i++)
	{
		if (s == ar[i])
			return true;
	}
	return false;
}

void main()
{
	cout << "Scanner output according to the input file tiny.txt" << endl << 
		"---------------------------------------------------" << endl;
	//Read a program sample in TINY language from file
	ifstream file("tiny.txt");
	string str;
	vector<pair<string, string>> output;
	string tmp = "";
	string reserved[8] = { "if", "then", "else", "end", "repeat", "until", "read", "write" };

	while (getline(file, str))
	{
		for (int i = 0; i < str.length(); i++)
		{
			//Identifiers & Reserved Words
			if (isalpha(str[i]))
			{
				while (isalpha(str[i]) || isdigit(str[i]))
				{
					tmp += str[i];
					i++;
				}
				if (check_reserved(tmp,reserved))
					output.push_back({ tmp, "RESERVED WORD" });
				else
					output.push_back({ tmp, "IDENTIFIER" });
				tmp = "";
			}
			//Comments
			if (str[i] == '{')
			{
				while (str[i] != '}')
				{
					tmp += str[i];
					i++;
				}
				tmp = "";
			}
			//Digits
			if (isdigit(str[i]))
			{
				while (isdigit(str[i]))
				{
					tmp += str[i];
					i++;
				}
				output.push_back({ tmp , "DIGIT" });
				tmp = "";
			}
			//Special Symbols
			switch (str[i])
			{
			case '+':
				output.push_back({ "+" , "PLUS" });
				break;
			case '-':
				output.push_back({ "-" , "MINUS" });
				break;
			case '*':
				output.push_back({ "*" , "MULTIPLY" });
				break;
			case '/':
				output.push_back({ "/" , "DIVID" });
				break;
			case '=':
				output.push_back({ "=" , "EQUAL" });
				break;
			case '<':
				output.push_back({ "<" , "SMALLER THAN" });
				break;
			case '>':
				output.push_back({ ">" , "BIGGER THAN" });
				break;
			case '(':
				output.push_back({ "(" , "LEFT BRACKET" });
				break;
			case ')':
				output.push_back({ ")" , "RIGHT BRACKET" });
				break;
			case ';':
				output.push_back({ ";" , "SEMI COLON" });
				break;
			case ':':
				if (str[i+1] == '=')
				{
					output.push_back({ ":=" , "ASSIGN" });
					i++;
				}
				break;
			}
		}
	}

	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i].first << "\t" << output[i].second << endl;
	}
}