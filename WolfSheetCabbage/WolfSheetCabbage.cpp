// WolfSheetCabbage.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dispatcher.h"
#include<iostream>


int main()
{
	Dispatcher dispatcher;
	dispatcher.queryPrograms();

	while (!dispatcher.isDone())
	{
		string program = dispatcher.getProgram();

		dispatcher.scheduling(program);

		if (dispatcher.isTragedy() || dispatcher.isRepeat())
		{
			dispatcher.restoreState();
			continue;
		}

		dispatcher.saveState();

		if (dispatcher.isSuccess())
		{
			dispatcher.printAllPrograms();
			//dispatcher.scheduling(program);
			dispatcher.restoreState();
			continue;
		}

		dispatcher.queryPrograms();
	}

    return 0;
}

