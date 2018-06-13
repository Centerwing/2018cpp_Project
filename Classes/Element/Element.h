#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include"cocos2d.h"

class Element : public cocos2d::Sprite
{
public:

	bool _isSelected;
	bool _isEnemy;

	unsigned _health;

	int _price;
};

#endif // !_ELEMENT_H_

