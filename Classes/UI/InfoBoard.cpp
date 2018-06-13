#include"InfoBoard.h"
#include"Element/Building.h"
#include"Element/Unit.h"
#include"Element/Element.h"
#include"Manager/MapLayer.h"
#include"Manager/GameManager.h"

#include"cocos2d.h"
#include"ui\UIButton.h"
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

	if (type == Building::BuildingType::BASE)
	{
		auto famer = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/famer.jpg" : "Element/p/famer.jpg");

		famer->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);
			
				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::FAMER);
					unit->setPosition(GameManager::getInstance()->_selectedBox->getPosition());

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

		fighter->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);

				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::WARRIOR);
					unit->setPosition(GameManager::getInstance()->_selectedBox->getPosition());

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

		warrior->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);

				if (GameManager::getInstance()->_money >= 50)
				{
					auto unit = Unit::create(Unit::UnitType::TANK);
					unit->setPosition(GameManager::getInstance()->_selectedBox->getPosition());

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

		barrack->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);

				/*创建图标跟随指针
				*/
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/barrack.png" : "Element/p/barrack.png");
				icon->setOpacity(80);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox->convertToNodeSpace(Vec2(event->getCursorX(),
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

				/* 点击建造的监听器
				 */
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) < 250 && GameManager::getInstance()->_money >= 150 && GameManager::getInstance()->_electric >= 10)
						{

							auto build = Building::create(Building::BuildingType::BARRACK);
							build->setPosition(loca);
							MapLayer::getInstance()->addChild(build);

							GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
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
						else if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) >= 250)
						{
							/*提示距离太远
							 */
							auto alert = Label::create("It's to far!", "fonts/arial.ttf", 32);
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

		crystal->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);

				/*创建图标跟随指针
				*/
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/crystal.png" : "Element/p/crystal.png");
				icon->setOpacity(100);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox->convertToNodeSpace(Vec2(event->getCursorX(),
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

				/* 点击建造的监听器
				*/
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) < 250 && GameManager::getInstance()->_money >= 100)
						{

							auto build = Building::create(Building::BuildingType::CRYSTAL);
							build->setPosition(loca);
							MapLayer::getInstance()->addChild(build);

							GameManager::getInstance()->getEventDispatcher()->removeEventListener(pListener);
							this->removeChildByTag(1);
						}

						else if (GameManager::getInstance()->_money < 100)
						{
							/*提示金钱不足
							*/
							auto alert = Label::create("Not enoough money!", "fonts/arial.ttf", 32);
							alert->setPosition(512, 226);
							this->addChild(alert, 1, 11);
							alert->scheduleOnce(schedule_selector(InfoBoard::removeAlertM), 3.0);
						}
						else if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) >= 250)
						{
							/*提示距离太远
							*/
							auto alert = Label::create("It's to far!", "fonts/arial.ttf", 32);
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

		crystal->setPosition(Vec2(870, 150));
		_board->addChild(crystal);



		/*====================建造机械厂按钮=======================*/
		auto machinery = ui::Button::create(GameManager::getInstance()->_team ? "Element/t/machinery_b.jpg" : "Element/p/machinery_b.jpg");

		machinery->addTouchEventListener([=](Ref* pRef, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto button = static_cast<ui::Button*>(pRef);

				/*创建图标跟随指针
				*/
				auto lis = EventListenerMouse::create();
				auto icon = Sprite::create(GameManager::getInstance()->_team ? "Element/t/machinery.png" : "Element/p/machinery.png");
				icon->setOpacity(100);
				addChild(icon, 1, 1);
				lis->onMouseMove = [=](EventMouse* event)
				{
					icon->setPosition(event->getCursorX(),
						event->getCursorY());

					if ((GameManager::getInstance()->_selectedBox->convertToNodeSpace(Vec2(event->getCursorX(),
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

				/* 点击建造的监听器
				*/
				auto pListener = EventListenerMouse::create();
				pListener->onMouseDown = [=](EventMouse* event)
				{
					if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
					{
						auto loca = MapLayer::getInstance()->convertToNodeSpace(event->getLocationInView());

						if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) < 250 && GameManager::getInstance()->_money >= 200 && GameManager::getInstance()->_electric >= 10)
						{

							auto build = Building::create(Building::BuildingType::MACHINERY);
							build->setPosition(loca);
							MapLayer::getInstance()->addChild(build);

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
						else if (loca.distance(GameManager::getInstance()->_selectedBox->getPosition()) >= 250)
						{
							/*提示距离太远
							*/
							auto alert = Label::create("It's to far!", "fonts/arial.ttf", 32);
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

		machinery->setPosition(Vec2(970, 150));
		_board->addChild(machinery);
	}

	else if (type == Unit::UnitType::WARRIOR)
	{

	}
	else if (type == Unit::UnitType::TANK)
	{

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
		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1500", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Base", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::BARRACK)
	{
		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1000", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Barrack", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::CRYSTAL)
	{
		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/400", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Crystal", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (build->_type == Building::BuildingType::MACHINERY)
	{
		auto pLabel = Label::create("Health: " + std::to_string(build->_health) + "/1250", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Machinery", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}

	// 实时显示血量
}


void InfoBoard::showInfo(Unit* unit)
{
	if (unit->_type == Unit::UnitType::FAMER)
	{
		auto pLabel = Label::create("Health: " + std::to_string(unit->_attr.health) + "/45", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Famer", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (unit->_type == Unit::UnitType::WARRIOR)
	{
		auto pLabel = Label::create("Health: " + std::to_string(unit->_attr.health) + "/45", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Fighter", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}
	else if (unit->_type == Unit::UnitType::TANK)
	{
		auto pLabel = Label::create("Health: " + std::to_string(unit->_attr.health) + "/125", "fonts/arial.ttf", 36);
		pLabel->setPosition(512, 100);
		_board->addChild(pLabel, 1);
		auto pTitle = Label::create("Warrior", "fonts/arial.ttf", 40);
		pTitle->setPosition(512, 150);
		_board->addChild(pTitle, 1);
	}

	// 实时显示血量
}


void InfoBoard::moneyInfoUpdate(float dt)
{
	removeChild(_moneyInfo);
	createMoneyInfo();

	//clearBoard();
}


void InfoBoard::createMoneyInfo()
{
	_moneyInfo = Label::create("crystal: " + std::to_string(GameManager::getInstance()->_money) +
		"  electric: " + std::to_string(GameManager::getInstance()->_electric), "fonts/arial.ttf", 24);
	_moneyInfo->enableGlow(Color4B::BLUE);
	_moneyInfo->setPosition(Vec2(860, 750));

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