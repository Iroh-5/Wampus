#include <iostream>
#include <vector>
#include <ctime> // for 'time' function
#include <string>
#include <sstream>

struct gameState
{
	bool isRunning;
	bool skip;
	int vampusPos;
	int playerPos;
	int pitPos[2];
	int batsPos[2];
	int arrowCount;
};

int cave[21][21] = { 
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{ -1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ -1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ -1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ -1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ -1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 }
};
// creates num random numbers between 1 and 21
// this is actually a Fisher-Yates shuffle algorithm
void shuffle(int* arr, int num)
{
	int tmpArr[21];
	for (int i = 1; i < 21; ++i)
		tmpArr[i] = i;
	for (int i = 0; i < num; ++i)
	{
		int ind = rand() % (20 - i) + 1;
		int tmp = tmpArr[ind];
		tmpArr[ind] = tmpArr[20 - i];
		tmpArr[20 - i] = tmp;
		arr[i] = tmp;
	}
}

void gameInit(gameState& gs)
{
	gs.isRunning = true;

	int positions[6];
	shuffle(positions, 6);

	gs.vampusPos  = positions[0];
	gs.playerPos  = positions[1];
	gs.pitPos[0]  = positions[2];
	gs.pitPos[1]  = positions[3];
	gs.batsPos[0] = positions[4];
	gs.batsPos[1] = positions[5];
	gs.arrowCount = 5;
	gs.skip = false;
}
// checks positions of player and other entities
void computerMove(gameState& gs)
{
	std::cout << "\nYOU ARE IN ROOM " << gs.playerPos << std::endl;

	if (gs.playerPos == gs.pitPos[0] || gs.playerPos == gs.pitPos[1])
	{
		std::cout << "YYYIIIIEEEE . . . FELL IN PIT" << std::endl;
		gs.isRunning = false;
		return;
	}
	else if (gs.playerPos == gs.vampusPos)
	{
		std::cout << "AUUGGHHHHH . . . VAMPUS ATE YOU" << std::endl;
		gs.isRunning = false;
		return;
	}
	else if (gs.playerPos == gs.batsPos[0] || gs.playerPos == gs.batsPos[1])
	{
		std::cout << "OOHHHH NOOOO . . . BATS THREW YOU AWAY" << std::endl;
		gs.playerPos = (rand() % 20) + 1;
		gs.skip = true;
		return;
	}

	for (int i = 1, k = 0; i < 21; ++i) // reconsinder: it may print message more than once. good or bad?
	{
		if (cave[gs.playerPos][i] == 1)
		{
			if (gs.vampusPos == i)
				std::cout << "IT SMELLS REALLY DISGUSTING. I AM ABOUT TO VOMIT" << std::endl;
			if (gs.pitPos[0] == i || gs.pitPos[1] == i)
				std::cout << "IT IS SO WINDY OUT THERE. I AM BARELY STANDING" << std::endl;
			if (gs.batsPos[0] == i || gs.batsPos[1] == i)
				std::cout << "OUGHH WHERE THIS LOUD NOISE COME FROM???" << std::endl;
		}
	}
	std::cout << '\n';
}

void playerMove(gameState& gs)
{
	if (gs.skip)
	{
		gs.skip = false;
		return;
	}
	if (!gs.isRunning)
		return;

	int tuns[3];
	for (int i = 1, k = 0; i < 21; ++i)
		if (cave[gs.playerPos][i] == 1)
			tuns[k++] = i;

	std::cout << "THE TUNNEL LEADS TO: " << tuns[0] << ' ' << tuns[1] << ' ' << tuns[2] << std::endl;

	std::cout << "SHOOT OR MOVE? (S-M) ";
	char ans;
	do
	{
		std::cin >> ans;
		ans = tolower(ans);
	} while (ans != 's' && ans != 'm');
	

	if (ans == 'm')
	{
		std::cout << "WHERE TO MOVE? ";
		int num;
		std::cin >> num;
		while (num != tuns[0] && num != tuns[1] && num != tuns[2])
		{
			std::cout << "ENTER CORRECT TUNNEL NUMBER" << std::endl;
			std::cin >> num;
		}
		gs.playerPos = num;
		return;
	}
	if (ans == 's')
	{
		// enters path in forman num1 num2 ... num5
		std::cin.ignore();
		std::cout << "ENTER PATH" << std::endl;
		std::vector<int> path;
		std::string pathStr;
		getline(std::cin, pathStr);
		std::istringstream oss{ pathStr };
		for (int n; oss >> n;)
			path.push_back(n);

		// determine wether the path is correct or not
		bool correct = true;
		if (path.size() > 1)
		{
			for (int i = 0; i < path.size() - 1; ++i)
				if (cave[path[i]][path[i + 1]] != 1)
				{
					correct = false;
					break;
				}
		}
		else
		{
			if (tuns[0] != path[0] && tuns[1] != path[0] && tuns[2] != path[0])
				correct = false;
		}

		int* newPath = new int[path.size()];
		if (!correct)
		{
			shuffle(newPath, path.size());
		}
		else
		{
			for (int i = 0; i < path.size(); ++i)
				newPath[i] = path[i];
		}

		for (int i = 0; i < path.size(); ++i)
		{
			if (newPath[i] == gs.vampusPos)
			{
				std::cout << "YAAAHHOOOO . . . VAMPUS IS DEAD. YOU WON" << std::endl;
				gs.isRunning = false;
				return;
			}
			if (newPath[i] == gs.playerPos)
			{
				std::cout << "AHAHAHAHA . . . THAT'S RIDICILOUS. YOU KILLED YOURSELF" << std::endl;
				gs.isRunning = false;
				return;
			}
		}
		delete[] newPath;

		std::cout << "NOTHING HAPPEND. BUT YOU LOST ONE ARROW AND WOKE UP THE VAMPUS" << std::endl;
		if (--gs.arrowCount == 0)
		{
			std::cout << "YOU'VE RUN OUT OF ARROWS. VAMPUS WON" << std::endl;
			gs.isRunning = false;
			return;
		}
		// vampus awaking
		int vN[3];
		for (int i = 1, k = 0; i < 21; ++i)
			if (cave[gs.vampusPos][i] == 1)
				vN[k++] = i;
		int rnd = rand() % 10;
		if (rnd >= 0 && rnd <= 3)
			return;
		else
		{
			gs.vampusPos = vN[rand() % 3];
			std::cout << "VAMPUS MOVED. BEWARE" << std::endl;
		}
	}
	std::cout << '\n';
}

int main()
{
	while (true)
	{
		srand(time(0));
		system("cls");
		gameState gs;
		gameInit(gs);

		std::cout << "---------------|" << "\nHUNT THE WUMPUS|\n" << "---------------|\n" << std::endl;

		while (gs.isRunning)
		{
			computerMove(gs);
			playerMove(gs);
		}

		std::cout << "PLAY AGAIN? (Y/N)" << std::endl;
		char ans;
		do
		{
			std::cin >> ans;
			ans = tolower(ans);
		} while (ans != 'y' && ans != 'n');
		if (ans == 'n')
			break;
	}

	return 0;
}