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

	pBuilding->_buildBar = ui::LoadingBar::create("gameScene/buildBar.png");
	pBuilding->_buildBar->setPercent(0);
	pBuilding->_buildBar->setPosition(pBuilding->getContentSize() / 2);
	pBuilding->addChild(pBuilding->_buildBar);

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
			if (this->getPhysicsBody()->isDynamic())
			{
				this->getPhysicsBody()->setDynamic(false);
			}

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

//各单位参数可以在这里设置
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
	case BuildingType::AIRPORT:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/airport.png" : "Element/p/airport.png");
		else
			this->initWithFile(GameManager::getInstance()->_team ? "Element/t/airport.png" : "Element/p/airport.png");
		this->_type = BuildingType::AIRPORT;
		this->_health = 1250;

		break;
	case BuildingType::ACADEMY:
		if (isEnemy)
			this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/academy.png" : "Element/p/academy.png");
		else
			this->initWithFile(GameManager::getInstance()->_team ? "Element/t/academy.png" : "Element/p/academy.png");
		this->_type = BuildingType::ACADEMY;
		this->_health = 750;

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
			animation->setDelayPerUnit(0.05);

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


void Building::buildUpdate(float dt)
{
	_buildBar->setPercent(_buildBar->getPercent() + 2);

	if (_buildBar->getPercent() == 100)
	{
		_buildBar->setPercent(0);
		
		Unit::UnitType type;
		if (this->_type == BuildingType::BASE)
		{
			type = Unit::UnitType::FAMER;
		}
		else if (this->_type == BuildingType::BARRACK)
		{
			type = Unit::UnitType::WARRIOR;
		}
		else if (this->_type == BuildingType::MACHINERY)
		{
			type = Unit::UnitType::TANK;
		}
		else if (this->_type == BuildingType::AIRPORT)
		{
			type = Unit::UnitType::GHOST;
		}

		auto unit = Unit::create(type);
		auto pos = this->getPosition();

		//加一个小的位置偏移
		pos.y -= 50;

		unit->setPosition(pos);
		unit->setTag(GameManager::getInstance()->_armyTag++);

		GameManager::getInstance()->createUnit(unit->_type, pos);

		MapLayer::getInstance()->addChild(unit);

		this->unschedule(schedule_selector(Building::buildUpdate));
	}
}


void Building::createUnit()
{
	_buildBar->setPercent(2);

	//单位建造时间可以在这里修改
	schedule(schedule_selector(Building::buildUpdate), 0.2);
}