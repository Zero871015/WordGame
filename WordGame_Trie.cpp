// Name: B10615032
// Date: 2018/05/15
// Last Update: 2018/05/18
// Problem statement: Word Game

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Define file name.
#define FILENAME "words.txt"
//Define the table size.
#define N 4

//A kind of search tree¡Xan ordered tree data structure that
//is used to store a dynamic set or associative array 
//where the keys are usually strings.
//More information refer Wiki:Trie.
struct Trie
{
	int isWord;		//0->not a word, 1->is a word, 2->need print, over 2-> already print.
	char letter;	//This node's letter.
	Trie* node[26];	//Next letter's node.
};


//Load the file into dictionary.
bool ReadFile(Trie dictionary[26]);
//Recursive to find the word.
void FindWord(Trie *t,string str, char map[N + 2][N + 2], int x, int y);

int main()
{
	Trie dictionary[26];	//26 numbers of trie,'a'~'z' beginning.
	
	//Initialize tries.
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			dictionary[i].node[j] = NULL;
		}
		dictionary[i].isWord = 0;
		dictionary[i].letter = 'a' + i;
	}

	//Latters map, plus 2 because of boundaries.
	char map[N + 2][N + 2] = {"\0"};
	
	//Load fail.
	if (!ReadFile(dictionary))
	{
		cout << "Reading file error!" << endl;
	}
	//Load success. Already build the tries through file.
	else
	{
		//Load map by cin.
		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 1; j < N + 1; j++)
			{
				cin >> map[i][j];
			}
		}
		
		//Run all of the words in tries.
		for (int i = 0; i < 26; i++)	//Loop all of the tries.
		{
			//Loop all of the board's number.
			for (int j = 0; j < N; j++)	
			{
				for (int k = 0; k < N; k++)
				{
					FindWord(&dictionary[i],"", map, j + 1, k + 1);
				}
			}
		}
	}
	system("pause");
	return 0;
}

bool ReadFile(Trie dictionary[26])
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
		string str;			//Catch the fstream.
		Trie *temp;			//Next node.
		Trie *nowBranch;	//Now node.

		//Build trie.
		while (!fin.eof())
		{
			fin >> str;

			//Through the beginning letter to find the trie. 
			nowBranch = &dictionary[str[0] - 'a'];
			for (int i = 1; i < (int)str.length(); i++)
			{
				//The node does not exist yet.
				if (nowBranch->node[str[i] - 'a'] == NULL)
				{
					temp = new Trie;

					//Initialize to new trie.
					for (int j = 0; j < 26; j++)
					{
						temp->node[j] = NULL;
					}
					//If this node is the end of the word, set isWord variable to 1.
					temp->isWord = ((i == str.length() - 1) ? 1 : 0);
					temp->letter = str[i];

					//Link the node.
					nowBranch->node[str[i] - 'a'] = temp;
					nowBranch = temp;
				}
				else
				{
					//The node Already exist, directly point to next node.
					nowBranch = nowBranch->node[str[i] - 'a'];
				}
			}
		}
		fin.close();
		return true;
	}
}

void FindWord(Trie *t,string str, char map[N + 2][N + 2], int x, int y)
{
	str += map[x][y];			//From beginning to this node, all of the node's letter combination.
	int oriLetter = map[x][y];	//Save the letter, for reset if return false in this branche.
	//If letter correct.
	if (map[x][y] == t->letter)
	{
		//If the word exist.
		if (t->isWord != 0)
		{
			//If not yet print.
			if (++t->isWord == 2)
				cout << str << endl;
		}
		map[x][y] = '\0';	//Can't use again.
		for (int i = 0; i < 26; i++)	//Loop all letters(nodes).
		{
			if (t->node[i])	//If the node exist.
			{
				//Run 8 directions.
				FindWord(t->node[i], str, map, x - 1, y - 1);
				FindWord(t->node[i], str, map, x - 1, y);
				FindWord(t->node[i], str, map, x - 1, y + 1);
				FindWord(t->node[i], str, map, x, y + 1);
				FindWord(t->node[i], str, map, x, y - 1);
				FindWord(t->node[i], str, map, x + 1, y - 1);
				FindWord(t->node[i], str, map, x + 1, y);
				FindWord(t->node[i], str, map, x + 1, y + 1);
			}
		}
		map[x][y] = oriLetter;	//Reset the letter.
	}
}
