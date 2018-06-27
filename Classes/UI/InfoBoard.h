#ifndef _INFOBOARD_H_
#define _INFOBOARD_H_

#include"cocos2d.h"

#include"Element/Building.h"
#include"Element/Unit.h"
#include"Element/Element.h"

USING_NS_CC;

class InfoBoard :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(InfoBoard);

	static InfoBoard* getInstance();
	void operator=(InfoBoard const &) = delete;

	void changeBoard(Building* building);
	void changeBoard(Unit* unit);
	
	void clearBoard();
private:
	void createBuildingButton(Building::BuildingType type);
	void createUnitButton(Unit::UnitType type);

	void showInfo(Building* building);
	void showInfo(Unit* unit);

	

	Sprite* _board;

	Label* _moneyInfo;
	void createMoneyInfo();

	void removeAlertM(float dt);
	void removeAlertE(float dt);
	void removeAlertF(float dt);

	void moneyInfoUpdate(float dt);

	void menuAttackCall(Ref* ref);


};

#endif // !_INFOBOARD_H_

