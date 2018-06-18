#ifndef _BUILDING_H_
#define _BUILDING_H_

#include"cocos2d.h"

#include"Element.h"

USING_NS_CC;

class Building : public Element
{
public:
	enum class BuildingType :std::uint8_t
	{
		BASE,
		BARRACK,
		CRYSTAL,
		MACHINERY
	} _type;

	static Building* create(BuildingType type, bool isEnemy = false);

	virtual void getDamage(unsigned damage);

	//bool _isSelected;
	//bool _isEnemy;

	//unsigned _electric;
	
private:

	void createListener();
	void createPhysics();

	void initBuilding(BuildingType type);

	void dying();
	void die();
};

#endif // !_BUILDING_H_

