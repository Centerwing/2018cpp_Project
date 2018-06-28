#ifndef _BUILDING_H_
#define _BUILDING_H_

#include"cocos2d.h"
#include"UI/CocosGUI.h"

#include"Element.h"
#include"Unit.h"

USING_NS_CC;

class Building : public Element
{
public:
	enum class BuildingType :std::uint8_t
	{
		BASE,
		BARRACK,
		CRYSTAL,
		MACHINERY,
		AIRPORT,
		ACADEMY
	} _type;

	static Building* create(BuildingType type, bool isEnemy = false);

	virtual void getDamage(unsigned damage);

	virtual void setSelected();
	virtual void unSelected();

	ui::LoadingBar* _buildBar;
	
	void createUnit();

private:
	Unit * _unit;
	Vec2 _pos;
	
	void buildUpdate(float dt);

	void createListener();
	void createPhysics();

	void initBuilding(BuildingType type,bool isEnemy);

	void die();
};

#endif // !_BUILDING_H_

