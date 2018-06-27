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

	pBuilding->initBuilding(type,isEnemy);
	pBuilding->createListener();
	pBuilding->createPhysics();

	pBuilding->_isSelected = false;
	pBuilding->_isEnemy = isEnemy;

	//pBuilding->autorelease();

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

				target->setSelected();
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
	pBody->setMass(80000);
	//pBody->setDynamic(false);

	this->setPhysicsBody(pBody);
}

/* 各单位参数可以在这里设置
 */
void Building::initBuilding(BuildingType type,bool isEnemy) 
{
	switch (type)
	{
	case BuildingType::BASE:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/base.png" : "Element/p/base.png");
		else
			this->initWithFile(GameManager::getInstance()->_team ? "Element/t/base.png" : "Element/p/base.png");
		this->_type = BuildingType::BASE;
		this->_health = 1500;
		break;
	case BuildingType::BARRACK:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/barrack.png" : "Element/p/barrack.png");
		else
			this->initWithFile(GameManager::getInstance()->_team ? "Element/t/barrack.png" : "Element/p/barrack.png");
		this->_type = BuildingType::BARRACK;
		this->_health = 1000;

		break;
	case BuildingType::CRYSTAL:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/crystal.png" : "Element/p/crystal.png");
		else
			this->initWithFile(GameManager::getInstance()->_team ? "Element/t/crystal.png" : "Element/p/crystal.png");
		this->_type = BuildingType::CRYSTAL;
		this->_health = 400;

		break;
	case BuildingType::MACHINERY:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/machinery.png" : "Element/p/machinery.png");
		else
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
	if (!GameManager::getInstance()->_selectedBox.empty() && GameManager::getInstance()->_selectedBox[0] == this)
	{
		GameManager::getInstance()->clearSelectedBox();

		InfoBoard::getInstance()->clearBoard();
	}

	if (this->_isEnemy)
	{
		GameManager::getInstance()->_enemyList.erase(this);
	}

	MapLayer::getInstance()->removeChild(this);

	if (this->_type == Building::BuildingType::BASE)
	{
		GameManager::getInstance()->gameOver(this->_isEnemy);
	}

	//this->release();
}


void Building::getDamage(unsigned damage)
{
	if (this->_health > 0)
	{
		this->_health -= damage;

		if (!GameManager::getInstance()->_selectedBox.empty() && GameManager::getInstance()->_selectedBox[0] == this)
		{
			InfoBoard::getInstance()->changeBoard(this);
		}

		if (this->_health <= 0)
		{
			auto animation = Animation::create();
			animation->addSpriteFrameWithFile("element/die/building/die1.png");
			animation->addSpriteFrameWithFile("element/die/building/die2.png");
			animation->addSpriteFrameWithFile("element/die/building/die3.png");
			animation->addSpriteFrameWithFile("element/die/building/die4.png");
			animation->addSpriteFrameWithFile("element/die/building/die5.png");
			animation->addSpriteFrameWithFile("element/die/building/die6.png");
			animation->setLoops(1);
			animation->setDelayPerUnit(0.04);

			auto animate = Animate::create(animation);

			auto die = CallFunc::create(CC_CALLBACK_0(Building::die, this));

			auto sequence = Sequence::create(animate, die, NULL);

			this->runAction(sequence);
		}
	}
}


void Building::setSelected()
{
	this->setColor(Color3B(150,255,150));
}


void Building::unSelected()
{
	this->setColor(Color3B(255, 255, 255));
}