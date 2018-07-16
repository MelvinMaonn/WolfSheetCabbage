#pragma once
#include<string>
#include<list>
#include<stack>
#include<iostream>
using namespace std;

class Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();
	bool isTragedy();
	bool isSuccess();
	void queryPrograms();
	bool isRepeat();
	//void restoreLastState(string program);
	void scheduling(string program);
	bool isDone();
	string getProgram();
	void printAllPrograms();
	void saveState();
	void restoreState();
private:
	string left;
	string right;
	int menPlace;
	list<string> leftState;
	list<string> rightState;
	stack<string> programStack;
	stack<int> programPos;
	stack<int> menPlaceStack;
};

