#include"Building.h"
#include"Manager/GameManager.h"
#include"Scene/GameScene.h"
#include"UI/InfoBoard.h"

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
				GameManager::getInstance()->_selectedBox = target;

				InfoBoard::getInstance()->changeBoard(this);

				target->setOpacity(200);
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

/* 建造每个单位的价钱将在这个函数里扣除
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
		GameManager::getInstance()->_money -= 150;
		GameManager::getInstance()->_electric -= 10;
		break;
	case BuildingType::CRYSTAL:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/crystal.png" : "Element/p/crystal.png");
		this->_type = BuildingType::CRYSTAL;
		this->_health = 400;
		GameManager::getInstance()->_money -= 100;
		GameManager::getInstance()->_electric += 5;
		break;
	case BuildingType::MACHINERY:
		this->initWithFile(GameManager::getInstance()->_team ? "Element/t/machinery.png" : "Element/p/machinery.png");
		this->_type = BuildingType::MACHINERY;
		this->_health = 1250;
		GameManager::getInstance()->_money -= 200;
		GameManager::getInstance()->_electric -= 10;
		break;
	default:
		break;
	}
}