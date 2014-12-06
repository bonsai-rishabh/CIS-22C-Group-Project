#pragma once

#include "HashTable\HashTable.h"
#include "HashTable\HashTableEntry.h"
#include "HashTable\HashTableTest.h"
#include "LinkedList.h"
#include "Team\Team.h"
#include "BST_nT.h"
#include "fileIO.h"
#include "UX.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <strstream>
vector<Team> getDivTeams(vector<Team> teams, int inDiv);
void exit(vector<Team> teams);
void efficeincies(vector<Team> teams, HashTable<int, Team> hashTable);
int treeSelection();
void buildTree(vector<Team> teams, CBinaryTree& tree);
void sortedOutputImp(int displayTeamsIn, vector<Team> teams, HashTable<int, Team> &hashTable);
void displayMenuImp(int passedVal)
{
	std::cout << "did something?" << std::endl;
};
void buildHash(vector<Team> teams, HashTable<int, Team> &hashTable)
{
	for (int i = 0; i < 32; i++)
	{
		hashTable.add(teams[i].keyOutput('y'), teams[i]);
	}
}
void editMenueImp(Team editTeam, int choice)
{
	int intInput;
	char charInput;
	std::cout << std::endl;
	std::cout << "Please Enter How Much you want to change the value" << std::endl;
	std::cin >> intInput;
	editTeam.changeVals(choice, intInput);
	std::cout << "Do You Want To Change Another Value? [Y/n]" << std::endl;
	std::cin >> charInput;
	if (charInput == 'y' || charInput == 'Y')
	{
		std::cout << "Which one?" << std::endl;
		std::cin >> intInput;
		editMenueImp(editTeam, intInput);
	}
	else if (charInput != 'n' && charInput != 'N')
	{
		std::cout << "You Entered an invalid input" << std::endl;

	}
}
void addMenuImp(vector<Team> teams, HashTable<int, Team> &hashTable)
{
	int intChoice;

	for (int i = 0; i < 32; i++)
	{
		std::cout << i + 1 << ")  " << teams[i] << std::endl;
	};
	std::cout << "Please Enter The Team You Want to Edit";
	std::cin >> intChoice;
	
}
void mainMenueImp(int choice, vector<Team> teams, HashTable<int, Team> hashTable)
{
	char charInput=' ';
	int intChoice;
	if (choice == 0)
		choice = mainMenu();
	switch (choice)
	{
	case 1:
		for (int i = 0; i < 32; i++)
		{
			std::cout << i + 1 << ")  " << teams[i] << std::endl;
		};
		std::cout << "Please Enter The Team You Want to Edit"<<std::endl;
		std::cin >> intChoice;
		intChoice -= 1;
		editMenueImp(teams[intChoice], editMenu());
		mainMenueImp(0, teams, hashTable);
		break;
	case 2:
		system("PAUSE");
		
		switch (displayTeams(teams))
		{

		default:
			break;
		}
		break;
	case 3:
		system("CLS");
		sortedOutputImp(displayTeams(teams), teams, hashTable);
		system("PAUSE");
		mainMenueImp(0, teams, hashTable);
		break;
	case 4:
		break;
	case 5:
		efficeincies(teams, hashTable);
		mainMenueImp(0, teams, hashTable);
		break;
	case 6:
		exit(teams);
			break;
	default:
		break;
		}
	}
void sortedOutputImp(int displayTeamsIn, vector<Team> teams, HashTable<int, Team> &hashTable)
{



	vector<Team> outPutVec;
	CBinaryTree tree;

	switch (displayTeamsIn)
	{
	case 0: mainMenueImp(0, teams, hashTable);
		break;
	case 1:
		switch (treeSelection())
		{
		case 0: mainMenueImp(0, teams, hashTable);
			break;
		case 1:  buildTree(teams, tree);
			tree.inorderTree(tree.root);
			break;
		default:
			break;
		}
	default:
		break;
	}
}


void implementation()
{
	HashTable<int, Team> hashTable;
	vector<Team> teams;
	char charInput;
	int intInput;
	


	std::string stringInput;
	
	landingPage();

	readDataInput(inputFilePrompt(), teams);
	buildHash(teams, hashTable);
	mainMenueImp(mainMenu(), teams, hashTable);
}


void buildTree(vector<Team> teams, CBinaryTree& tree)
{
	for (int i = 0; i <= 31; i++)
	{
		tree.insertNode(teams[i].keyOutput('y'), teams[i]);
	};
}

int treeSelection()
{
	int selection;
	std::cout << "Please Select Which Value you would like to sort by" << std::endl;
	std::cout 
		<< "1)Yards" << std::endl 
		<< "2)Wins" << std::endl 
		<< "3)Losses" <<std::endl 
		<< "4)PPI" << std::endl 
		<< "5)Name" << std::endl;
	std::cin >> selection;
	return selection;
}

void efficeincies(vector<Team> teams, HashTable<int,Team> hashTable)
{
	system("CLS");
	std::cout << "There was a load factor of " << hashTable.getLoad() << " in this instance " << std::endl;
	std::cout << "Please note: due to the structure of the NFL and a set amount of teams the load factor will be 1 barring any errors in the amount of teams" << std::endl;
	system("PAUSE");
}

void exit(vector<Team> teams)
{
	char charInput;
	std::cout << "Are You Sure You Want To Exit? [Y/n]" << std::endl;
	std::cin >> charInput;
	if (charInput != 'n' || charInput != 'N')
	{
		std::cout << "Do You Want To Output any changes to a text file? [Y/n]" << std::endl;
		std::cin >> charInput;
		if (charInput == 'y' || charInput == 'Y')
		{
			Output(teams);
		}
	}
	std::cout << "Goodbye" << std::endl;
}

vector<Team> playoffBracket(vector<Team> teams, HashTable<int, Team> hashTable)
{
	vector<Team> bracket;
	vector<Team> bracketAFC;
	vector<Team> bracketNFC;
	vector<Team> currDiv;
	vector<Team> temp;
	Team test;
	int currPPI, testPPI, divScalar = 0;
	bool done;


	for (int i = 1; i <= 4; i++)
	{
		//NFC Playoff bracket no wildcard
		currDiv = getDivTeams(teams, i);
		for (int k = 0; k <= 3; k++)
		{
			divScalar += currDiv[k].keyOutput('p');
		}
		divScalar /= 4000;
		test = currDiv[0];
		for (int j = 1; j <= 3; j++)
		{
			testPPI = test.keyOutput('p');
			testPPI *= divScalar;
			currPPI = currDiv[j].keyOutput('p');
			currPPI *= divScalar;
			if (currPPI > testPPI)
			{
				test = currDiv[j];
			}
		}
		bracketNFC.push_back(test);
	}
	for (int i = 0; i <= 31; i++)
	{

	}

	return bracket;
}


vector<Team> getDivTeams(vector<Team> teams, int inDiv)
{
	vector<Team> retVal;

	for (int i = 0; i <= 31; i++)
	{
		if (teams[i].getDivVal() == inDiv)
		{
			retVal.push_back(teams[i]);
		}
	}
	return retVal;
}