#include "Networking.h"

std::vector<std::string> Networking::numbers;
std::string Networking::newNumber = { "054" };
int Networking::change;
bool Networking::changedNumbers;

Networking::Networking()
{

}

Networking::~Networking()
{

}

//This is where we read from site.html file and store all the data that was commented about in the header file of this .cpp file
void Networking::NetworkingInitialise()
{
	std::ifstream read("site.html");
	std::string hold;
	while (getline(read, temp))
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if ((temp[i] == '0' || temp[i] == '1' || temp[i] == '2' || temp[i] == '3' || temp[i] == '4' || temp[i] == '5' || temp[i] == '6' || temp[i] == '7' || temp[i] == '8' || temp[i] == '9')
				&& (temp[i - 2] == '0' || temp[i - 2] == '1' || temp[i - 2] == '2' || temp[i - 2] == '3' || temp[i - 2] == '4' || temp[i - 2] == '5' || temp[i - 2] == '6' || temp[i - 2] == '7' || temp[i - 2] == '8' || temp[i - 2] == '9'))
			{
				hold.push_back(temp[i - 2]);
				hold.push_back(temp[i - 1]);
				hold.push_back(temp[i]);
				numbers.push_back(hold);
				hold = {};
			}
		}
		fileLines.push_back(temp);
	}
	change = 0;
	changedNumbers = false;
}

//How the highscore change works is that we push back into the numbers vector the new highscore, we sort them all and then delete the last element
void Networking::NetworkingChange()
{
	if (change == 5)
	{
		change++;
		numbers.push_back(newNumber);
		std::sort(numbers.begin(), numbers.end());
		numbers.pop_back();
		changedNumbers = true;
		NetworkingUpload();
	}
}

//The upload works extremely similar to how the initialize works, but instead, this time we change all of the high scores to the ones scored in numbers
void Networking::NetworkingUpload()
{
	std::ofstream out("site.html");
	int counter = 0;
	for (int i = 0; i < fileLines.size(); i++)
	{
		for (int j = 0; j < fileLines[i].size(); j++)
		{
			if ((fileLines[i][j] == '0' || fileLines[i][j] == '1' || fileLines[i][j] == '2' || fileLines[i][j] == '3' || fileLines[i][j] == '4' || fileLines[i][j] == '5' || fileLines[i][j] == '6' || fileLines[i][j] == '7' || fileLines[i][j] == '8' || fileLines[i][j] == '9') &&
				(fileLines[i][j - 2] == '0' || fileLines[i][j - 2] == '1' || fileLines[i][j - 2] == '2' || fileLines[i][j - 2] == '3' || fileLines[i][j - 2] == '4' || fileLines[i][j - 2] == '5' || fileLines[i][j - 2] == '6' || fileLines[i][j - 2] == '7' || fileLines[i][j - 2] == '8' || fileLines[i][j - 2] == '9'))
			{
				fileLines[i][j - 2] = numbers[counter][0];
				fileLines[i][j - 1] = numbers[counter][1];
				fileLines[i][j] = numbers[counter][2];
				counter++;
			}
		}
	}
	for (int x = 0; x < fileLines.size(); x++)
	{
		out << fileLines[x];
	}
	changedNumbers = false;
}
