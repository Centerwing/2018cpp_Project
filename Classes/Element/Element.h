#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include"cocos2d.h"

class Element : public cocos2d::Sprite
{
public:

	bool _isSelected;
	bool _isEnemy;
	bool _attackMode;

	int _price;
	int _health;
	virtual void getDamage(unsigned damage)=0;

	virtual void setSelected()=0;
	virtual void unSelected()=0;
private:

};

#endif // !_ELEMENT_H_

