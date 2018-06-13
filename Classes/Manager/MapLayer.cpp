#include"cocos2d.h"

#include"MapLayer.h"

USING_NS_CC;

bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto pSpr = Sprite::create("map/map.png");
	pSpr->setAnchorPoint(Vec2(0, 0));
	pSpr->setPosition(Vec2(0, 0));

	addChild(pSpr,-1);
	
	createWalls();
}


MapLayer* MapLayer::getInstance()
{
	static MapLayer* _instance = MapLayer::create();

	return _instance;
}


void MapLayer::createWalls()
{
	auto pw1 = Sprite::create("map/wall_u.png");
	pw1->setAnchorPoint(Vec2(0, 1));
	pw1->setPosition(Vec2(130, 3200));
	auto pb1 = PhysicsBody::createBox(pw1->getContentSize());
	pb1->setDynamic(false);
	pw1->setPhysicsBody(pb1);
	this->addChild(pw1, -2);
	
	auto pw2 = Sprite::create("map/wall_u.png");
	pw2->setAnchorPoint(Vec2(0, 0));
	pw2->setPosition(Vec2(641, 0));
	auto pb2 = PhysicsBody::createBox(pw2->getContentSize());
	pb2->setDynamic(false);
	pw2->setPhysicsBody(pb2);
	this->addChild(pw2, -2);

	auto pw3 = Sprite::create("map/wall_l.png");
	pw3->setAnchorPoint(Vec2(0, 0));
	pw3->setPosition(Vec2(0, 0));
	auto pb3 = PhysicsBody::createBox(pw3->getContentSize());
	pb3->setDynamic(false);
	pw3->setPhysicsBody(pb3);
	this->addChild(pw3, -2);

	auto pw4 = Sprite::create("map/wall_l.png");
	pw4->setAnchorPoint(Vec2(0, 0));
	pw4->setPosition(Vec2(3071, 0));
	auto pb4 = PhysicsBody::createBox(pw4->getContentSize());
	pb4->setDynamic(false);
	pw4->setPhysicsBody(pb4);
	this->addChild(pw4, -2);

	auto pw5 = Sprite::create("map/wall_cl.png");
	pw5->setAnchorPoint(Vec2(0, 0));
	pw5->setPosition(Vec2(130, 1662));
	auto pb5 = PhysicsBody::createBox(pw5->getContentSize());
	pb5->setDynamic(false);
	pw5->setPhysicsBody(pb5);
	this->addChild(pw5, -2);

	auto pw6 = Sprite::create("map/wall_cl.png");
	pw6->setAnchorPoint(Vec2(0, 0));
	pw6->setPosition(Vec2(2806, 1184));
	auto pb6 = PhysicsBody::createBox(pw6->getContentSize());
	pb6->setDynamic(false);
	pw6->setPhysicsBody(pb6);
	this->addChild(pw6, -2);

	auto pw7 = Sprite::create("map/wall_c.png");
	pw7->setPosition(Vec2(1600, 1600));
	auto pb7 = PhysicsBody::createBox(pw7->getContentSize());
	pb7->setDynamic(false);
	pw7->setPhysicsBody(pb7);
	this->addChild(pw7, -2);

	auto pw8 = Sprite::create("map/wall_cu.png");
	pw8->setAnchorPoint(Vec2(0, 0));
	pw8->setPosition(Vec2(1020, 135));
	auto pb8 = PhysicsBody::createBox(pw8->getContentSize());
	pb8->setDynamic(false);
	pw8->setPhysicsBody(pb8);
	this->addChild(pw8, -2);

	auto pw9 = Sprite::create("map/wall_cu.png");
	pw9->setAnchorPoint(Vec2(0, 0));
	pw9->setPosition(Vec2(1024, 2816));
	auto pb9 = PhysicsBody::createBox(pw9->getContentSize());
	pb9->setDynamic(false);
	pw9->setPhysicsBody(pb9);
	this->addChild(pw9, -2);

}