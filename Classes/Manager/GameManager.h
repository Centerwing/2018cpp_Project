#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include"cocos2d.h"
#include<vector>

#include"Element/Element.h"

USING_NS_CC;

#define SALARY_MAX 50;//√øŒÂ√Î
#define ORIGIN_SALARY 0;
#define ORIGIN_MONEY 150;
#define ORIGIN_ELECTRIC 10;

class GameManager :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameManager);

	static GameManager* getInstance();
	void operator=(GameManager const &) = delete;
	
	Element* _selectedBox;
	void clearSelectedBox();

	int _money;
	int _electric;
	int _salary;
	bool _team;//true = terran , false = protoss
private:
	void salaryUpdate(float dt);
};

#endif // !_GAMEMANAGER_H_

