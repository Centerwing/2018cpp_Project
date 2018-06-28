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
		TANK,
		GHOST
	} _type;

	static Unit* create(UnitType type, bool isEnemy = false);

	struct Attr
	{
		unsigned attack;
		float speed;
		//¹¥»÷·¶Î§
		float range;
	} _attr;

	enum class Status:std::uint8_t
	{
		STAND,
		MOVE,
		ATTACK
	} _status;

	void attack(Element* target);
	void move(Vec2 pos);

	virtual void getDamage(unsigned damage);	

	virtual void setSelected();
	virtual void unSelected();
private:

	void createListener();
	void createPhysics();

	void initUnit(UnitType type, bool isEnemy);

	void attackUpdate(float dt);

	Animate* _attackAnima;

	Sprite* _bullet;
	void removeBullet();

	void die();
};

#endif // !_UNIT_H_

