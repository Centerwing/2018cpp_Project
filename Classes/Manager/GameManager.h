#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include"cocos2d.h"
#include<set>
#include<vector>

#include"Element/Element.h"
#include"Element/Unit.h"
#include"Network/Client.h"
#include"Element/Building.h"
#include"Element/Unit.h"

USING_NS_CC;

#define SALARY_MAX 5 //每0.5秒
#define ORIGIN_SALARY 0
#define SALARY_ONE 1
#define ORIGIN_MONEY 1000
#define ORIGIN_ELECTRIC 10

//int _armyTag = 100;
//int _enemyTag = 200;

class GameManager :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameManager);

	static GameManager* getInstance();
	void operator=(GameManager const &) = delete;

	void unitMove(int tag, int x, int y);
	void unitAttack(int attacker, int target);

	void createBuilding(Building::BuildingType type, Vec2 pos);
	void createUnit(Unit::UnitType type, Vec2 pos);
	
	std::vector<Element*> _selectedBox;
	void clearSelectedBox();

	std::set<Element*> _enemyList;
	std::set<Unit*> _unitList;

	int _money;
	int _electric;
	int _salary;

	//标识单位用于网络传输
	int _armyTag;
	int _enemyTag;

    //true = terran , false = protoss
	bool _team;
	bool _enemyTeam;

	void gameOver(bool win);
private:
	Client * client;

	std::vector<Rect> _mine;
	void initMine();

	void over(float dt);

	void salaryUpdate(float dt);

	void onEnter();
	void onExit();

	void onMove(const void* msg);

	void onAttack(const void* msg);

	void onCreateBuilding(const void* msg);

	void onCreateUnit(const void* msg);
};

#endif // !_GAMEMANAGER_H_

