#include"Element.h"
#include"Manager/MapLayer.h"

#include"cocos2d.h"

void Element::getDamage(unsigned damage)
{
	MapLayer::getInstance()->removeChild(this);
}