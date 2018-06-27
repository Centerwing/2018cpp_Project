#include"GameScene.h"
#include"Element/Unit.h"
#include"Element/Building.h"
#include"Manager/GameManager.h"
#include"UI/InfoBoard.h"
#include"Manager/MapLayer.h"
#include"Element/User.h"

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

	schedule(schedule_selector(GameScene::MapMoveUpdate),1.0/60);

	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/ShortChangeHero.mp3", true);
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4);
	}

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


void GameScene::createMap()
{
	this->_map = MapLayer::getInstance();
	_map->setPosition(0, -2430);

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


/**
*根据_roomNumber
*初始化游戏场景
*/
void GameScene::initGame()
{
	//第一个进房间的出生在左上角
	if (!User::getInstance()->_roomNumber)
	{
		//产生友军
		auto base = Building::create(Building::BuildingType::BASE);
		base->setPosition(Vec2(440, 2950));
		base->setTag(GameManager::getInstance()->_armyTag++);
		MapLayer::getInstance()->addChild(base);

		auto famer = Unit::create(Unit::UnitType::FAMER);
		famer->setPosition(Vec2(600, 2950));
		famer->setTag(GameManager::getInstance()->_armyTag++);
		MapLayer::getInstance()->addChild(famer);

		//产生敌军
		auto base2 = Building::create(Building::BuildingType::BASE, true);
		base2->setPosition(Vec2(2770, 360));
		base2->setTag(GameManager::getInstance()->_enemyTag++);
		MapLayer::getInstance()->addChild(base2);

		auto famer2 = Unit::create(Unit::UnitType::FAMER, true);
		famer2->setPosition(Vec2(2600, 350));
		famer2->setTag(GameManager::getInstance()->_enemyTag++);
		MapLayer::getInstance()->addChild(famer2);
	}
	//第二个进房间的出生在右下角
	else
	{
		//产生敌军
		auto base = Building::create(Building::BuildingType::BASE,true);
		base->setPosition(Vec2(440, 2950));
		base->setTag(GameManager::getInstance()->_enemyTag++);
		MapLayer::getInstance()->addChild(base);

		auto famer = Unit::create(Unit::UnitType::FAMER,true);
		famer->setPosition(Vec2(600, 2950));
		famer->setTag(GameManager::getInstance()->_enemyTag++);
		MapLayer::getInstance()->addChild(famer);

		//产生友军
		auto base2 = Building::create(Building::BuildingType::BASE);
		base2->setPosition(Vec2(2770, 360));
		base2->setTag(GameManager::getInstance()->_armyTag++);
		MapLayer::getInstance()->addChild(base2);

		auto famer2 = Unit::create(Unit::UnitType::FAMER);
		famer2->setPosition(Vec2(2600, 350));
		famer2->setTag(GameManager::getInstance()->_armyTag++);
		MapLayer::getInstance()->addChild(famer2);

		//重设地图位置
		_map->setPosition(Vec2(-2175, 210));
	}
}