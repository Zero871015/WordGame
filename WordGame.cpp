// Name: B10615032
// Date: 2018/05/15
// Last Update: 2018/05/15
// Problem statement: Word Game

#include <iostream>
#include <fstream>
#include <set>
#include <string>
using namespace std;

//Define file name.
#define FILENAME "words.txt"
//Define the table size.
#define N 4

//Load the file into dictionary.
bool ReadFile(set<string>* words);
//Recursive to find the word.
bool FindWord(string target, string nowWord, char map[N + 2][N + 2], int x, int y);

int main()
{
	set<string> words;					//dictionary
	char map[N + 2][N + 2] = {"\0"};	//latters map, plus 2 because of boundaries
	
	//Load fail.
	if (!ReadFile(&words))
	{
		cout << "Reading file error!" << endl;
	}
	//Load success.
	else
	{
		//Save the original map.
		char oriMap[N + 2][N + 2] = {"\0"};

		//Load map by cin.
		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 1; j < N + 1; j++)
			{
				cin >> map[i][j];
				oriMap[i][j] = map[i][j];
			}
		}
		
		//Run all of the words in dictionary.
		for (set<string>::iterator it = words.begin(); it !=words.end(); it++)
		{
			string temp = *it;
			//Try N*N initial positions.
			for (int i = 0; i < N*N; i++)
			{
				if (FindWord(temp, "", map, (i % N) + 1, (i / N) + 1))
				{
					//If find the word, reset map.
					for (int j = 1; j < N+1; j++)
					{
						for (int k = 1; k < N+1; k++)
						{
							map[j][k] = oriMap[j][k];
						}
					}
					break;
				}
			}
		}
	}
	system("pause");
	return 0;
}

bool ReadFile(set<string>* words)
{
	fstream fin;
	fin.open(FILENAME, ios::in);

	//Can't not open file.
	if (fin.fail())
	{
		return false;
	}
	else
	{
		string temp;
		//Add word into dictionary.
		while (!fin.eof())
		{
			fin >> temp;
			words->insert(temp);
		}
		fin.close();
		return true;
	}
}

bool FindWord(string target, string nowWord, char map[N + 2][N + 2], int x, int y)
{
	int oriLetter = map[x][y];	//Save the letter, for reset if return false in this branche.
	
	//If letter correct.
	if (map[x][y] == target[nowWord.length()])
	{
		nowWord += target[nowWord.length()];
		map[x][y] = '\0';	//Can't use again.
	}
	//Wrong letter.
	else
	{
		return false;
	}

	//Already complete string.
	if (nowWord == target)
	{
		cout << target << endl;
		return true;
	}
	//Keep trying.
	else
	{
		//Try 8 directions.
		if ((FindWord(target, nowWord, map, x - 1, y - 1) ||
			FindWord(target, nowWord, map, x - 1, y) ||
			FindWord(target, nowWord, map, x - 1, y + 1) ||
			FindWord(target, nowWord, map, x, y - 1) ||
			FindWord(target, nowWord, map, x, y + 1) ||
			FindWord(target, nowWord, map, x + 1, y - 1) ||
			FindWord(target, nowWord, map, x + 1, y) ||
			FindWord(target, nowWord, map, x + 1, y + 1)) == false)
		{
			map[x][y] = oriLetter;	//Reset the letter.
			return false;
		}
		else
			return true;
	}
}