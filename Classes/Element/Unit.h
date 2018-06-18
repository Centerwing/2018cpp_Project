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
		unsigned attack;
		float speed;
		float range;
	} _attr;

	enum class Status:std::uint8_t
	{
		STAND,
		MOVE,
		ATTACK
	} _status;

	//void changeMode();

	//bool _isEnemy;
	//bool _isSelected;

	virtual void getDamage(unsigned damage);
private:

	void createListener();
	void createPhysics();

	void initUnit(UnitType type);

	void attackUpdate(float dt);
	void attack(Vec2 target);

	Sprite* _bullet;
	void removeBullet();

	void dying();
	void die();
};

#endif // !_UNIT_H_

