#include <iostream>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctype.h>
#include <fstream>
#include <string.h>

using namespace std;

string get_word()
{
	srand(time(NULL));
	ifstream infile("nouns.txt");
	string line;
	vector<string> words;
	while (getline(infile, line))
	{
		words.push_back(line);
	}

	int num = rand()%words.size();
	return words[num];

}

int main() {
	WINDOW* window;
	window = initscr();
	bool close = false;

	vector<char> used;
	vector<char> usable;

	for (char c = 64; c < 91; c++) usable.push_back(c);

	bool solved = true;
	string word;
	char* cword = (char*)word.c_str();
	char  cword2[128];

	int lives=5;

	bool win = false;
	bool lose = false;

	while (!close)
	{
		if (solved)
		{
			word = get_word();
			for (int i = 0; i < word.size(); i++)
			{
				cword2[i]='_';
			}
			cword = (char*)word.c_str();
			solved=false;
		}

		mvprintw(6, 1, "Lives: %i", lives);
		mvprintw(7, 1, cword2);
		mvprintw(0, 1, "User Chars: ");

		for (int i = 0; i < used.size(); i++)
		{
			stringstream ss;
			string s;
			ss << used[i];
			ss >> s;
			mvprintw(1, i+1, "%s", s.c_str());
		}
		mvprintw(5, 1, "Enter Letter: ");
		refresh();

		char ch = getchar();
		if (isalpha(ch))
		{
			if (find(used.begin(), used.end(), toupper(ch)) == used.end())
			{
				used.push_back(toupper(ch));
				if (strchr(cword, ch) == NULL) { lives-=1; }
				else
				{
					for (int i = 0; i < strlen(cword); i++)
					{
						if (cword[i] == ch)
						{cword2[i] = ch;}
					}
				}
			}
		}
		else if (ch == 27)
		{
			endwin();
			close = true;
		}

		if (lives<=0) { mvprintw(6, 1, "Lives: %i", lives); close=true; lose=true; }
		if (string(cword) == string(cword2)) { mvprintw(7, 1, cword2); close=true; win=true; }

	}

	if (win)
	{
		clear();
		mvprintw(2, 1, "Word Was: %s", cword);
		mvprintw(3, 1, "YOU WON!");
		getch();
	}
	else if (lose)
	{
		clear();
		mvprintw(2, 1, "Word Was: %s", cword);
		mvprintw(3, 1, "YOU LOST!");
		getch();
	}
	endwin();

  return 0;
}