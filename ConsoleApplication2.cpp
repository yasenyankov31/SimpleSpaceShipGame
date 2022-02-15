
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <cstring>
#include<algorithm>


#define VK_RIGHT          0x27
#define VK_LEFT           0x25
#define VK_SPACE	      0x20

using namespace std;

void Render(string board[10][12])
{
	for (int i = 0; i < 10; i++)
	{
		string line = "";
		for (int j = 0; j < 12; j++)
		{
			line += board[i][j];
		}
		cout << line << endl;
	}

}

int Find_index(string line[12], string variable)
{

	for (int i = 1; i < 11; i++)
	{
		if (line[i] == variable)
		{
			return i;
		}
	}

}

string* GenerateAstroid()
{
	string* astro_arr = new string[12];
	for (int i = 1; i < 10; i++)
	{
		int iSecret = rand() % rand() % 10 + 1 + 1;
		if (iSecret > 5)
		{
			astro_arr[i] = 'D';
		}
		else
		{
			astro_arr[i] = '  ';
		}
	}
	astro_arr[0] = '*';
	astro_arr[11] = '*';

	return astro_arr;
}

void MoveBullet(string board[10][12])
{
	for (int i = 10; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			if (board[i][j] == "b")
			{
				auto var = board[i][j];
				board[i][j] = board[i - 1][j];
				board[i - 1][j] = var;
				i--;
			}
			if (board[0][j] == "b")
			{
				board[0][j] = " ";
			}
		}
	}

}

void MoveAstroid(string board[10][12])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (board[i][j] == "D")
			{
				swap(board[i], board[i + 1]);
				i += 2;

			}
		}
	}

}


int main()
{
	int score = 0;
	string* obstacle;
	string board[10][12];
	int bullet = 1;
	string player = "A";

	string player_line[12];
	player_line[0] = "*";
	player_line[11] = "*";
	int counter = 3;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			board[i][j] = " ";
		}
		board[i][0] = "*";
		board[i][11] = "*";
	}
	for (int j = 1; j < 10; j++)
	{
		if (j == 5)
			board[9][j] = player;
		else
			board[9][j] = " ";
	}
	board[9][0] = "*";
	board[9][11] = "*";
	//Generate board

	while (true)
	{
		string* foo = std::find(std::begin(board[8]), std::end(board[8]), "D");

		if (foo != std::end(board[8]))
		{
			if (board[8][Find_index(board[9], player)] == "D")
				break;
			else
			{
				for (int j = 1; j < 10; j++)
				{
					board[8][j] = " ";
				}
				board[8][0] = "*";
				board[8][11] = "*";
			}
		}
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				if (board[i][j] == "b" && board[i - 1][j] == "D")
				{
					board[i][j] = " ";
					board[i - 1][j] = " ";
				}
				else if (board[i][j] == "b" && board[i + 1][j] == "D")
				{
					board[i][j] = " ";
					board[i + 1][j] = " ";
				}
			}
		}

		if (counter == 3)
		{
			obstacle = GenerateAstroid();
			copy_n(obstacle, 12, board[0]);
			counter = 0;
			bullet = 1;
		}




		MoveAstroid(board);

		MoveBullet(board);


		if (GetAsyncKeyState(VK_SPACE) != 0 && GetAsyncKeyState(VK_SPACE) != 1 && bullet == 1)
		{
			board[8][Find_index(board[9], player)] = "b";
			bullet = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) != 0 && GetAsyncKeyState(VK_RIGHT) != 1)
		{

			for (int i = 1; i < 10; i++)
			{
				if (board[9][i] == "A")
				{
					auto var = board[9][i];
					board[9][i] = board[9][i + 1];
					board[9][i + 1] = var;
					break;
				}

			}

		}
		if (GetAsyncKeyState(VK_LEFT) != 0 && GetAsyncKeyState(VK_LEFT) != 1)
		{

			for (int i = 10; i > 1; i--)
			{
				if (board[9][i] == "A")
				{
					auto var = board[9][i];
					board[9][i] = board[9][i - 1];
					board[9][i - 1] = var;
					break;
				}

			}

		}

		Render(board);
		this_thread::sleep_for(chrono::milliseconds(100));
		system("cls");
		counter++;
		score += 100;
	}
	cout << "GAME OVER!" << " YOUR SCORE IS " << score << " !" << endl; ;


}

