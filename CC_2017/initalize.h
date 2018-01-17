#include "stdafx.h"

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <random>

namespace initalize
{
	static int gId = 0;

	struct QuestScript
	{
		int	   id_;
		int	   next_;
		std::string name;
		QuestScript(const int id = -1) : id_(id)
		{
			next_ = ++gId;
		}
		QuestScript() : id_(rand() % 10000)
		{
			next_ = ++gId;
		}
	};

	class QuestManager
	{
		using QuestPtr = std::shared_ptr<QuestScript>;
		using QuestData = pair<int, QuestPtr>;
		using QusetMap = map<int, QuestPtr>;

		QusetMap questMap;
		QuestPtr curScript;

	public:

		QuestManager()
		{
			clear();
			create();
		}

		void create()
		{
			default_random_engine dre;
			uniform_int_distribution<int> uid(0, 100);

			questMap.insert(QuestData(-1, std::make_shared<QuestScript>(-1)));

			for (int i = 0; i < 10; ++i)
				questMap.insert(QuestData(i, std::make_shared<QuestScript>(i)));

			curScript = questMap[-1];

		}
		void clear()
		{
			questMap.clear();
		}

		void nextQuest(const int curIndex)
		{
			if (QuestData data = *(questMap.find(curIndex)); data.second == curScript)
			{
				curScript = questMap[curScript->next_];
			}

			switch (QuestData data = *(questMap.find(curIndex)); data.first)
			{
			case 0:
				std::cout << data.second->id_ << std::endl;
				break;
			case 1:
				std::cout << data.second->id_ << std::endl;
				break;
			default:
				cout << "default : " << data.second->id_ << endl;
				break;
			}
		}
		void show()
		{
			nextQuest(-1);
			nextQuest(curScript->id_);
			nextQuest(curScript->id_);
			nextQuest(curScript->id_);
		}
	};

	void start()
	{
		QuestManager manager;
		manager.show();
	}

}
