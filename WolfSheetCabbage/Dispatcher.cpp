#include "stdafx.h"
#include "Dispatcher.h"


Dispatcher::Dispatcher()
{
	left = "MWSG";
	right = "";
	menPlace = 0;
	leftState.push_back(left);
	rightState.push_back(right);
}


Dispatcher::~Dispatcher()
{
}

bool Dispatcher::isTragedy()
{
	if (menPlace == 0)
	{
		if (right.find("S")!=right.npos && (right.find("W") != right.npos || right.find("G") != right.npos))
		{
			return true;
		}
	}
	else
	{
		if (left.find("S") != left.npos && (left.find("W") != left.npos || left.find("G") != left.npos))
		{
			return true;
		}
	}
	
	return false;
}

bool Dispatcher::isSuccess()
{
	if (right.find("M")!= right.npos && right.find("W") != right.npos && right.find("S") != right.npos && right.find("G") != right.npos)
	{
		return true;
	}

	return false;
}

void Dispatcher::queryPrograms()
{
	int num = 0;
	string temp;
	if (menPlace == 0)
	{
		temp = left;
		num = left.length();
		temp.erase(left.find("M"),1);
	}
	else
	{
		temp = right;
		num = right.length();
		temp.erase(right.find("M"),1);
		
	}
	string* programs = new string[num];
	for (int i = 0; i < temp.length(); i++)
	{
		programStack.push(temp.substr(i, 1) + "M");
		programPos.push(rightState.size());
		menPlaceStack.push(menPlace);
	}
	programStack.push("M");
	programPos.push(rightState.size());
	menPlaceStack.push(menPlace);
}

bool Dispatcher::isRepeat()
{
	list<string>::iterator iter;
	for (iter = rightState.begin(); iter != rightState.end(); iter++)
	{

		if ((*iter).length() != right.length())
		{
			continue;
		}

		if ((*iter).compare("") == 0)
		{
			return true;
		}

		int repeat = true;
		for (int i = 0; i < right.length(); i++)
		{
			if ((*iter).find(right.substr(i,1)) == (*iter).npos)
			{
				repeat = false;
				break;
			}
		}
		
		if (repeat)
		{
			return true;
		}
	}
	return false;
}

void Dispatcher::scheduling(string program)
{
	if (menPlace == 0)
	{
		menPlace = 1;
		for (int i = 0; i < program.length(); i++)
		{
			
			left = left.erase(left.find(program.substr(i,1)),1);
			right = right.append(program.substr(i,1)+"");
		}
	}
	else
	{
		menPlace = 0;
		for (int i = 0; i < program.length(); i++)
		{
			right = right.erase(right.find(program.substr(i, 1)),1);
			left = left.append(program.substr(i,1) + "");
		}
	}
	
}

bool Dispatcher::isDone()
{
	return programStack.empty();
}

string Dispatcher::getProgram()
{
	string program = programStack.top();
	programStack.pop();
	programPos.pop();
	menPlaceStack.pop();
	return program;
}

void Dispatcher::printAllPrograms()
{
	list<string>::iterator iter;
	for (iter = rightState.begin(); iter != rightState.end(); iter++)
	{
		cout << *iter << endl;
	}
}

void Dispatcher::saveState()
{
	leftState.push_back(left);
	rightState.push_back(right);
}

void Dispatcher::restoreState()
{
	if (programPos.empty())
	{
		return;
	}

	for (int i = rightState.size()-1; i >= programPos.top(); i--)
	{
		leftState.pop_back();
		rightState.pop_back();
	}

	left = leftState.back();
	right = rightState.back();
	menPlace = menPlaceStack.top();
}


