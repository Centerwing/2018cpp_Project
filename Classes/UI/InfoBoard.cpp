#include"InfoBoard.h"
#include"Element/Building.h"
#include"Element/Unit.h"
#include"Element/Element.h"
#include"Manager/MapLayer.h"
#include"Manager/GameManager.h"

#include"cocos2d.h"
#include"ui/UIButton.h"
#include"UI/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include<string>

USING_NS_CC;

bool InfoBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_board = Sprite::create("GameScene/infoBoard.png");
	_board->setPosition(Vec2(_board->getContentSize() / 2));
	this->addChild(_board);

	createMoneyInfo();

	schedule(schedule_selector(InfoBoard::moneyInfoUpdate), 0.5f);

	return true;
}


InfoBoard* InfoBoard::getInstance()
{
	static InfoBoard* _instance = InfoBoard::create();

	return _instance;
}


void InfoBoard::createBuildingButton(Building::BuildingType type)
{	
	//Unit建造价钱在这里修改
	if (type == Building::BuildingType::BASE)
	{
		auto famer = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/famer.jpg" : "Element/p/famer.jpg");

		famer->setSwallowTouches(true);

		famer->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);
			
				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::FAMER);
					auto pos = GameManager::getInstance()->_selectedBox[0]->getPosition();

					//加一个小的位置偏移，防止两面位置不同步
					pos.y += 50;

					unit->setPosition(pos);
					GameManager::getInstance()->_money -= 50;
					//GameManager::getInstance()->_salary += 10;

					unit->setTag(GameManager::getInstance()->_armyTag++);

					GameManager::getInstance()->createUnit(Unit::UnitType::FAMER, pos);

					MapLayer::getInstance()->addChild(unit);
				}	
				else if (GameManager::getInstance()->_money < 50)
				{
					/* 提示金钱不足
					 */
					auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
					alert->setPosition(512, 226);
					this->addChild(alert, 1, 11);
					alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
				}
			}
		});


		famer->setPosition(Vec2(770, 150));
	    _board->addChild(famer,1);
	}
		
	else if (type == Building::BuildingType::BARRACK)
	{
		auto fighter = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/fighter.jpg" : "Element/p/fighter.jpg");

		fighter->setSwallowTouches(true);

		fighter->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);

				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::WARRIOR);
					auto pos = GameManager::getInstance()->_selectedBox[0]->getPosition();

					//加一个小的位置偏移，防止两面位置不同步
					pos.y += 50;

					unit->setPosition(pos);
					GameManager::getInstance()->_money -= 75;

					unit->setTag(GameManager::getInstance()->_armyTag++);

					GameManager::getInstance()->createUnit(Unit::UnitType::WARRIOR, pos);

					MapLayer::getInstance()->addChild(unit);
				}
				else if (GameManager::getInstance()->_money < 50)
				{
					/* 提示金钱不足
					*/
					auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
					alert->setPosition(512, 226);
					this->addChild(alert, 1, 11);
					alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
				}
			}
		});


		fighter->setPosition(Vec2(770, 150));
		_board->addChild(fighter, 1);
	}

	else if (type == Building::BuildingType::CRYSTAL)
	{
		return;
	}

	else if (type == Building::BuildingType::MACHINERY)
	{
		auto warrior = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/warrior.jpg" : "Element/p/warrior.jpg");

		warrior->setSwallowTouches(true);

		warrior->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);

				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::TANK);
					auto pos = GameManager::getInstance()->_selectedBox[0]->getPosition();

					//加一个小的位置偏移，防止两面位置不同步
					pos.y += 50;

					unit->setPosition(pos);
					GameManager::getInstance()->_money -= 125;

					unit->setTag(GameManager::getInstance()->_armyTag++);

					GameManager::getInstance()->createUnit(Unit::UnitType::TANK, pos);

					MapLayer::getInstance()->addChild(unit);
				}
				else if (GameManager::getInstance()->_money < 50)
				{
					//提示金钱不足
					auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
					alert->setPosition(512, 226);
					this->addChild(alert, 1, 11);
					alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
				}
			}
		});


		warrior->setPosition(Vec2(770, 150));
		_board->addChild(warrior, 1);
	}


}


void InfoBoard::createUnitButton(Unit::UnitType type)
{

	if (type == Unit::UnitType::FAMER)
	{
		/*====================建造兵营按钮=======================*/
		auto barrack = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/barrack_b.jpg" : "Element/p/barrack_b.jpg");

		barrack->setSwallowTouches(true);

		barrack->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);

				//创建图标跟随指针
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/barrack.png" : "Element/p/barrack.png");
				icon->setOpacity(80);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox[0]->convertToNodeSpace(Vec2(event->getCursorX(),
						event->getCursorY()))).length() < 250.0)
					{
						icon->setColor(Color3B::GREEN);
					}
					else
					{
						icon->setColor(Color3B::RED);
					}

				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, icon);

				//点击建造的监听器
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) < 250 && GameManager::getInstance()->_money >= 150 && GameManager::getInstance()->_electric >= 10)
						{
							if (UserDefault::getInstance()->
								getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

							auto build = Building::create(Building::BuildingType::BARRACK);
							build->setPosition(loca);

							build->setTag(GameManager::getInstance()->_armyTag++);

							GameManager::getInstance()->createBuilding(Building::BuildingType::BARRACK, loca);

							MapLayer::getInstance()->addChild(build);
							GameManager::getInstance()->_money -= 150;
							GameManager::getInstance()->_electric -= 10;

							GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
							//去除图标跟随
							this->removeChildByTag(1);
						}

						else if (GameManager::getInstance()->_money < 150)
						{
							/*提示金钱不足
							 */
							auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 226);
							this->addChild(alert, 1, 11);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
						}

						else if (GameManager::getInstance()->_electric < 10)
						{
							/*提示电力不足
							 */
							auto alert = Label::create("Not enoough electric!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 256);
							this->addChild(alert, 1, 12);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertE), 3.0);
						}
						else if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) >= 250)
						{
							/*提示距离太远
							 */
							auto alert = Label::create("It's too far!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 286);
							this->addChild(alert, 1, 13);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertF), 3.0);
						}

					}

					/*取消点击建造的事件监听
					 *取消图标跟随
					 */
					else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
					{
						GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
						this->removeChildByTag(1);
					}
				};
				GameManager::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, GameManager::getInstance());
			}
		});

		barrack->setPosition(Vec2(770, 150));
		_board->addChild(barrack);


		/*====================建造水晶按钮=======================*/
		auto crystal = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/crystal_b.jpg" : "Element/p/crystal_b.jpg");

		crystal->setSwallowTouches(true);

		crystal->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);

				//创建图标跟随指针
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/crystal.png" : "Element/p/crystal.png");
				icon->setOpacity(100);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox[0]->convertToNodeSpace(Vec2(event->getCursorX(),
						event->getCursorY()))).length() < 250.0)
					{
						icon->setColor(Color3B::GREEN);
					}
					else
					{
						icon->setColor(Color3B::RED);
					}

				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, icon);

				//点击建造的监听器
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) < 250 && GameManager::getInstance()->_money >= 100)
						{
							if (UserDefault::getInstance()->
								getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

							auto build = Building::create(Building::BuildingType::CRYSTAL);
							build->setPosition(loca);

							build->setTag(GameManager::getInstance()->_armyTag++);

							GameManager::getInstance()->createBuilding(Building::BuildingType::CRYSTAL, loca);

							MapLayer::getInstance()->addChild(build);
							GameManager::getInstance()->_money -= 100;
							GameManager::getInstance()->_electric += 5;

							GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
							this->removeChildByTag(1);
						}

						else if (GameManager::getInstance()->_money < 100)
						{
							//提示金钱不足
							auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 226);
							this->addChild(alert, 1, 11);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
						}
						else if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) >= 250)
						{
							//提示距离太远
							auto alert = Label::create("It's too far!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 286);
							this->addChild(alert, 1, 13);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertF), 3.0);
						}

					}

					/**
					*取消点击建造的事件监听
					*取消图标跟随
					*/
					else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
					{
						GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
						this->removeChildByTag(1);
					}
				};
				GameManager::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, GameManager::getInstance());
			}
		});

		crystal->setPosition(Vec2(870, 150));
		_board->addChild(crystal);



		/*====================建造机械厂按钮=======================*/
		auto machinery = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/machinery_b.jpg" : "Element/p/machinery_b.jpg");

		machinery->setSwallowTouches(true);

		machinery->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

				auto button = static_cast<ui::Button*>(pRef);

				//创建图标跟随指针
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/machinery.png" : "Element/p/machinery.png");
				icon->setOpacity(100);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox[0]->convertToNodeSpace(Vec2(event->getCursorX(),
						event->getCursorY()))).length() < 250.0)
					{
						icon->setColor(Color3B::GREEN);
					}
					else
					{
						icon->setColor(Color3B::RED);
					}

				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, icon);

				//点击建造的监听器
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) < 250 && GameManager::getInstance()->_money >= 200 && GameManager::getInstance()->_electric >= 10)
						{
							if (UserDefault::getInstance()->
								getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

							auto build = Building::create(Building::BuildingType::MACHINERY);
							build->setPosition(loca);

							build->setTag(GameManager::getInstance()->_armyTag++);

							GameManager::getInstance()->createBuilding(Building::BuildingType::MACHINERY, loca);

							MapLayer::getInstance()->addChild(build);
							GameManager::getInstance()->_money -= 200;
							GameManager::getInstance()->_electric -= 10;

							GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
							this->removeChildByTag(1);
						}

						else if (GameManager::getInstance()->_money < 200)
						{
							/*提示金钱不足
							*/
							auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 226);
							this->addChild(alert, 1, 11);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
						}

						else if (GameManager::getInstance()->_electric < 10)
						{
							/*提示电力不足
							*/
							auto alert = Label::create("Not enoough electric!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 256);
							this->addChild(alert, 1, 12);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertE), 3.0);
						}
						else if (loca.distance(GameManager::getInstance()->_selectedBox[0]->getPosition()) >= 250)
						{
							/*提示距离太远
							*/
							auto alert = Label::create("It's too far!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 286);
							this->addChild(alert, 1, 13);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertF), 3.0);
						}

					}

					/**
					*取消点击建造的事件监听
					*取消图标跟随
					*/
					else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
					{
						GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
						this->removeChildByTag(1);
					}
				};
				GameManager::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, GameManager::getInstance());
			}
		});

		machinery->setPosition(Vec2(970, 150));
		_board->addChild(machinery);
	}

	else if (type == Unit::UnitType::WARRIOR)
	{
		auto on = Sprite::create("element/attack/attack.png");
		auto off = Sprite::create("element/attack/disattack.png");

		auto menuOn = MenuItemSprite::create(on, on);
		auto menuOff = MenuItemSprite::create(off, off);
		auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(InfoBoard::menuAttackCall, this), menuOff, menuOn, NULL);
		if (GameManager::getInstance()->_selectedBox[0]->_attackMode)
		{
			toggle->setSelectedIndex(1);
		}
		else
		{
			toggle->setSelectedIndex(0);
		}

		auto menu = Menu::create(toggle, nullptr);
		menu->setPosition(Vec2(770, 150));
		_board->addChild(menu, 0);
	}
	else if (type == Unit::UnitType::TANK)
	{
		auto on = Sprite::create("element/attack/attack.png");
		auto off = Sprite::create("element/attack/disattack.png");

		auto menuOn = MenuItemSprite::create(on, on);
		auto menuOff = MenuItemSprite::create(off, off);
		auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(InfoBoard::menuAttackCall, this), menuOff, menuOn, NULL);
		if (GameManager::getInstance()->_selectedBox[0]->_attackMode)
		{
			toggle->setSelectedIndex(1);
		}
		else
		{
			toggle->setSelectedIndex(0);
		}

		auto menu = Menu::create(toggle, nullptr);
		menu->setPosition(Vec2(770, 150));
		_board->addChild(menu, 0);
	}
}


void InfoBoard::menuAttackCall(Ref* ref)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/move.mp3");

	for (auto iter : GameManager::getInstance()->_selectedBox)
	{
		iter->_attackMode = !iter->_attackMode;
	}
}


void InfoBoard::changeBoard(Building* building)
{
	clearBoard();

	if(!building->_isEnemy)createBuildingButton(building->_type);
	showInfo(building);
}


void InfoBoard::changeBoard(Unit* unit)
{
	clearBoard();

	if (!unit->_isEnemy)createUnitButton(unit->_type);
	showInfo(unit);
}


void InfoBoard::clearBoard()
{
	_board->removeAllChildren();
}


void InfoBoard::showInfo(Building* build)
{
	if (build->_type == Building::BuildingType::BASE)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(build->_health * 100 / 1500);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1500", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Base", "fonts/arial.ttf", 40);
		pTitle->setTextColor(build->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::BARRACK)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(build->_health * 100 / 1000);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1000", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Barrack", "fonts/arial.ttf", 40);
		pTitle->setTextColor(build->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::CRYSTAL)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(build->_health * 100 / 400);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/400", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Crystal", "fonts/arial.ttf", 40);
		pTitle->setTextColor(build->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::MACHINERY)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(build->_health * 100 / 1250);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1250", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Machinery", "fonts/arial.ttf", 40);
		pTitle->setTextColor(build->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
}


void InfoBoard::showInfo(Unit* unit)
{
	if (unit->_type == Unit::UnitType::FAMER)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(unit->_health * 100 / 45);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(unit->_health) + "/45", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Famer", "fonts/arial.ttf", 40);
		pTitle->setTextColor(unit->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (unit->_type == Unit::UnitType::WARRIOR)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(unit->_health * 100 / 45);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(unit->_health) + "/45", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Fighter", "fonts/arial.ttf", 40);
		pTitle->setTextColor(unit->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (unit->_type == Unit::UnitType::TANK)
	{
		auto health = ui::LoadingBar::create("gameScene/healthBar.png");
		health->setPercent(unit->_health * 100 / 125);
		health->setPosition(Vec2(512, 100));
		_board->addChild(health, 1);

		auto pLabel = Label::create("Health: " + std::to_string(unit->_health) + "/125", "fonts/arial.ttf", 24);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 2);

		auto pTitle = Label::create("Warrior", "fonts/arial.ttf", 40);
		pTitle->setTextColor(unit->_isEnemy ? Color4B::RED : Color4B::GREEN);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
}


void InfoBoard::moneyInfoUpdate(float dt)
{
	removeChild(_moneyInfo);

	createMoneyInfo();
}


void InfoBoard::createMoneyInfo()
{
	_moneyInfo = Label::create("crystal: " + std::to_string(GameManager::getInstance()->_money) +
		"(+" + std::to_string(GameManager::getInstance()->_salary) + ")"
		"  electric: " + std::to_string(GameManager::getInstance()->_electric),
		"fonts/arial.ttf", 24);
	_moneyInfo->enableGlow(Color4B::BLUE);
	_moneyInfo->setPosition(Vec2(850, 750));

	addChild(_moneyInfo,1);
}


void InfoBoard::removeAlertM(float dt)
{
	InfoBoard::getInstance()->removeChildByTag(11);
}


void InfoBoard::removeAlertE(float dt)
{
	InfoBoard::getInstance()->removeChildByTag(12);
}


void InfoBoard::removeAlertF(float dt)
{
	InfoBoard::getInstance()->removeChildByTag(13);
}