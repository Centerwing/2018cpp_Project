#ifndef _UNIT_H_
#define _UNIT_H_

#include"cocos2d.h"

#include"Element.h"

USING_NS_CC;

class Unit :public Element
{
public:
	
	enum class UnitType:std::uint8_t
	{
		FAMER,
		WARRIOR,
		TANK
	} _type;

	static Unit* create(UnitType type, bool isEnemy = false);

	struct Attr
	{
		unsigned health;
		unsigned attack;
		float speed;
	} _attr;

	enum class Status:std::uint8_t
	{
		STAND,
		MOVE,
		ATTACK
	} _status;

	void getDamage(unsigned damage);

	//bool _isEnemy;
	//bool _isSelected;
	bool _attackMod;
private:

	void createListener();
	void createPhysics();

	void initUnit(UnitType type);
};

#endif // !_UNIT_H_

