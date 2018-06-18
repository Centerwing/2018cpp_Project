#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include"cocos2d.h"
#include<set>
#include<vector>

#include"Element/Element.h"
#include"Element/Unit.h"

USING_NS_CC;

#define SALARY_MAX 50;//每五秒
#define ORIGIN_SALARY 10;
#define ORIGIN_MONEY 150;
#define ORIGIN_ELECTRIC 10;

class GameManager :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameManager);

	static GameManager* getInstance();
	void operator=(GameManager const &) = delete;
	
	std::vector<Element*> _selectedBox;
	void clearSelectedBox();

	std::set<Element*> _enemyList;
	std::set<Unit*> _unitList;

	int _money;
	int _electric;
	int _salary;
	bool _team;//true = terran , false = protoss
	bool _enemyTeam;  ////////////////////////////////////这里还没实现
private:
	void salaryUpdate(float dt);
};

#endif // !_GAMEMANAGER_H_

