#include"Building.h"
#include"Manager/GameManager.h"
#include"Scene/GameScene.h"
#include"UI/InfoBoard.h"
#include"Manager/MapLayer.h"

#include"cocos2d.h"

USING_NS_CC;

Building* Building::create(BuildingType type,bool isEnemy)
{
	auto pBuilding = new Building;

	pBuilding->initBuilding(type);
	pBuilding->createListener();
	pBuilding->createPhysics();

	pBuilding->_isSelected = false;
	pBuilding->_isEnemy = isEnemy;

	pBuilding->autorelease();

	if (isEnemy)
		GameManager::getInstance()->_enemyList.insert(pBuilding);

	return pBuilding;
}


void Building::createListener()
{
	auto pListener = EventListenerMouse::create();
	pListener->onMouseDown = [=](EventMouse* event)
	{
		Vec2 location = event->getLocationInView();
		auto target = static_cast<Building*>(event->getCurrentTarget());

		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			Vec2 locationInNode = target->convertToNodeSpace(location);
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				GameManager::getInstance()->clearSelectedBox();
				GameManager::getInstance()->_selectedBox.push_back(target);

				InfoBoard::getInstance()->changeBoard(this);

				target->setOpacity(180);
				target->_isSelected = true;
			}
			else
				return;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}


void Building::createPhysics()
{
	PhysicsBody* pBody = PhysicsBody::createBox(this->getContentSize());
	pBody->setGravityEnable(false);
	pBody->setRotationEnable(false);
	pBody->setMass(60000);
	//pBody->setDynamic(false);

	this->setPhysicsBody(pBody);
}

/* 各单位参数可以在这里设置
 */
void Building::initBuilding(BuildingType type) 
{
	switch (type)
	{
	case BuildingType::BASE:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/base.png" : "Element/p/base.png");  
		this->_type = BuildingType::BASE;
		this->_health = 1500;
		break;
	case BuildingType::BARRACK:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/barrack.png" : "Element/p/barrack.png");
		this->_type = BuildingType::BARRACK;
		this->_health = 1000;

		break;
	case BuildingType::CRYSTAL:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/crystal.png" : "Element/p/crystal.png");
		this->_type = BuildingType::CRYSTAL;
		this->_health = 400;

		break;
	case BuildingType::MACHINERY:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/machinery.png" : "Element/p/machinery.png");
		this->_type = BuildingType::MACHINERY;
		this->_health = 1250;

		break;
	default:
		break;
	}
	this->_attackMode = false;
	this->_isSelected = false;
}


void Building::die()
{
	MapLayer::getInstance()->removeChild(this);
	if (this->_isEnemy)
	{
		GameManager::getInstance()->_enemyList.erase(this);
	}

	this->release();
}


void Building::dying()
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("element/die/building/die1.png");
	animation->addSpriteFrameWithFile("element/die/building/die2.png");
	animation->addSpriteFrameWithFile("element/die/building/die3.png");
	animation->addSpriteFrameWithFile("element/die/building/die4.png");
	animation->addSpriteFrameWithFile("element/die/building/die5.png");
    animation->addSpriteFrameWithFile("element/die/building/die6.png");
	animation->addSpriteFrameWithFile("element/die/building/die7.png");////////////////////
	animation->setLoops(1);
	animation->setDelayPerUnit(0.04);

	auto animate = Animate::create(animation);

	auto todie = CallFunc::create(CC_CALLBACK_0(Building::die, this));

	auto sequence = Sequence::create(animate, todie, NULL);

	//如果不先去除PhysicsBody 会有点小bug
	this->getPhysicsBody()->removeFromWorld();
	this->runAction(sequence);
}


void Building::getDamage(unsigned damage)
{
	this->_health -= damage;
	if (this->_health < 0)
	{
		//死亡之后延迟播放动画，与被击中同步
		auto delay = DelayTime::create(0.4);
		auto dy = CallFunc::create(CC_CALLBACK_0(Building::dying, this));
		auto sequence = Sequence::create(delay, dy, NULL);

		this->runAction(sequence);
	}
}