#include"GameScene.h"
#include"Element/Unit.h"
#include"Element/Building.h"
#include"Manager/GameManager.h"
#include"UI/InfoBoard.h"
#include"Manager/MapLayer.h"

#include"cocos2d.h"
#include<windows.h>
#include"SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();


	createMap();

	createManager();

	createInfoBoard();

	initGame();

	//===========create listener==========
	//createMouseListener();

	schedule(schedule_selector(GameScene::MapMoveUpdate),1.0/60);

	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/ShortChangeHero.mp3", true);
	
	//===========test code==============



	return true;
}



void GameScene::MapMoveUpdate(float dt)
{
	//get cursor position
	LPPOINT pt=new POINT;
	GetCursorPos(pt);
	
	//get window position
	LPRECT rect=new RECT;
	GetWindowRect(GetForegroundWindow(), rect);

	if ((pt->x) > rect->right - 30
		&& _map->getPosition().x > -3190 + visibleSize.width)
		_map->setPosition(_map->getPosition().x - 10, _map->getPosition().y);

	if ((pt->x) < rect->left + 30
		&& _map->getPosition().x < 0)
		_map->setPosition(_map->getPosition().x + 10, _map->getPosition().y);

	if ((pt->y) > rect->top + 50
		&& _map->getPosition().y < 214)
		_map->setPosition(_map->getPosition().x, _map->getPosition().y + 10);

	if ((pt->y) < rect->bottom - 30
		&& _map->getPosition().y > -3190 + visibleSize.height)
		_map->setPosition(_map->getPosition().x, _map->getPosition().y - 10);

	delete pt;
	delete rect;
}


/*void GameScene::createMouseListener()
{
	auto pListener = EventListenerMouse::create();
	pListener->onMouseDown = [=](EventMouse* event)
	{
		float x = event->getCursorX();
		float y = event->getCursorY();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}*/


void GameScene::createMap()
{
	this->_map = MapLayer::getInstance();

	addChild(_map, 1);
}


void GameScene::createManager()
{
	this->_manager = GameManager::getInstance();
	
	addChild(_manager,-1);
}


void GameScene::createInfoBoard()
{
	this->_infoBoard = InfoBoard::getInstance();

	addChild(_infoBoard, 2);
}


void GameScene::initGame()
{
	GameManager::getInstance()->_money = ORIGIN_MONEY;
	GameManager::getInstance()->_salary = ORIGIN_SALARY;
	GameManager::getInstance()->_electric = ORIGIN_ELECTRIC;

	auto base = Building::create(Building::BuildingType::BASE);
	base->setPosition(Vec2(500, 500));
	MapLayer::getInstance()->addChild(base);

	auto famer = Unit::create(Unit::UnitType::FAMER);
	famer->setPosition(Vec2(250, 250));
	MapLayer::getInstance()->addChild(famer);

	auto enemy = Unit::create(Unit::UnitType::WARRIOR,true);
	enemy->setPosition(Vec2(750, 750));
	MapLayer::getInstance()->addChild(enemy);

	auto warrior = Unit::create(Unit::UnitType::WARRIOR);
	warrior->setPosition(Vec2(1000, 750));
	MapLayer::getInstance()->addChild(warrior);

	auto tan = Unit::create(Unit::UnitType::TANK);
	tan->setPosition(Vec2(1000,1000));
	MapLayer::getInstance()->addChild(tan);

	auto bui = Building::create(Building::BuildingType::BARRACK,true);
	bui->setPosition(1250, 1250);
	MapLayer::getInstance()->addChild(bui);
}