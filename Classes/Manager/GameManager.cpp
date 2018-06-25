#include"GameManager.h"
#include"Element/User.h"
#include"Network/MyGame_generated.h"
#include"MapLayer.h"

#include"cocos2d.h"

USING_NS_CC;
using namespace MyGame;

bool GameManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_team = User::getInstance()->_team;
	_enemyTeam = User::getInstance()->_enemyTeam;

	_armyTag = User::getInstance()->_roomNumber ? 200 : 100;
	_enemyTag = User::getInstance()->_roomNumber ? 100 : 200;

	_money = ORIGIN_MONEY;
	_salary = ORIGIN_SALARY;
	_electric = ORIGIN_ELECTRIC;

	initMine();

	schedule(schedule_selector(GameManager::salaryUpdate), 0.5f);
	
	return true;
}


GameManager* GameManager::getInstance()
{
	static GameManager* _instance = GameManager::create();

	return _instance;
}


void GameManager::clearSelectedBox()
{
	for (auto iter : _selectedBox)
	{
		iter->_isSelected = false;
		iter->setOpacity(255);
	}
	_selectedBox.clear();
}


void GameManager::initMine()
{
	Rect m1(125, 2860, 72, 128);
	Rect m2(198, 2764, 73, 335);
	Rect m3(267, 3063, 77, 64);
	Rect m4(2598, 130, 441, 88);
	Rect m5(2528, 194, 77, 64);
	_mine.push_back(m1);
	_mine.push_back(m2);
	_mine.push_back(m3);
	_mine.push_back(m4);
	_mine.push_back(m5);
}


void GameManager::salaryUpdate(float dt)
{
	_salary = 0;

	for (auto iter : _unitList)
	{
		if (iter->_type == Unit::UnitType::FAMER)
		{
			for (auto range : _mine)
			{
				if (range.containsPoint(iter->getPosition()))
				{
					_salary += SALARY_ONE;
					break;
				}
			}
		}
	}

	if (_salary > SALARY_MAX)
	{
		_salary = SALARY_MAX;
	}

	_money += _salary;
}


void GameManager::onEnter()
{
	Layer::onEnter();
#ifdef NETWORK
	client = Client::getInstance();
	if (!client->isConnected()) client->connect();

	CLIENT_ON(MsgType_Move, GameManager::onMove);
	CLIENT_ON(MsgType_Attack, GameManager::onAttack);
	CLIENT_ON(MsgType_CreBuilding, GameManager::onCreateBuilding);
	CLIENT_ON(MsgType_CreUnit, GameManager::onCreateUnit);
#endif // NETWORK
}


void GameManager::onExit()
{
#ifdef NETWORK
    client->close();

	client->clear();
	client = nullptr;
#endif // NETWORK
	Layer::onExit();
}


void GameManager::unitMove(int tag, int x, int y)
{
	flatbuffers::FlatBufferBuilder builder;
	auto info = CreateMove(builder, tag, x, y);
	MsgBuilder msg(builder);
	msg.add_type(MsgType::MsgType_Move);
	msg.add_data_type(Info_Move);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);
	client->send(builder.GetBufferPointer(), builder.GetSize());
}


void GameManager::unitAttack(int attacker, int target)
{
	flatbuffers::FlatBufferBuilder builder;
	auto info = CreateAttack(builder, attacker, target);
	MsgBuilder msg(builder);
	msg.add_type(MsgType::MsgType_Attack);
	msg.add_data_type(Info_Attack);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);
	client->send(builder.GetBufferPointer(), builder.GetSize());
}


void GameManager::onMove(const void* msg)
{
	auto data = static_cast<const Move*>(msg);
	auto target = static_cast<Unit*>(MapLayer::getInstance()->getChildByTag(data->tag()));
	Vec2 pos(data->x(), data->y());

	target->move(pos);
}


void GameManager::onAttack(const void* msg)
{
	auto data = static_cast<const Attack*>(msg);
	auto attacker = static_cast<Unit*>(MapLayer::getInstance()->getChildByTag(data->attacker()));
	auto target = static_cast<Element*>(MapLayer::getInstance()->getChildByTag(data->target()));

	attacker->attack(target);
}


void GameManager::createBuilding(Building::BuildingType type, Vec2 pos)
{
	flatbuffers::FlatBufferBuilder builder;
	int ty = static_cast<int>(type);
	auto info = CreateCreBuilding(builder, ty, pos.x, pos.y);
	MsgBuilder msg(builder);
	msg.add_type(MsgType_CreBuilding);
	msg.add_data_type(Info_CreBuilding);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);

	client->send(builder.GetBufferPointer(), builder.GetSize());
}


void GameManager::onCreateBuilding(const void* msg)
{
	auto data = static_cast<const CreBuilding*>(msg);
	
	Vec2 pos(data->x(), data->y());

	auto build = Building::create(static_cast<Building::BuildingType>(data->type()), true);
	build->setPosition(pos);
	build->setTag(GameManager::getInstance()->_enemyTag++);

	MapLayer::getInstance()->addChild(build);
}


void GameManager::createUnit(Unit::UnitType type, Vec2 pos)
{
	flatbuffers::FlatBufferBuilder builder;
	int ty = static_cast<int>(type);
	auto info = CreateCreBuilding(builder, ty, pos.x, pos.y);
	MsgBuilder msg(builder);
	msg.add_type(MsgType_CreUnit);
	msg.add_data_type(Info_CreUnit);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);

	client->send(builder.GetBufferPointer(), builder.GetSize());
}


void GameManager::onCreateUnit(const void* msg)
{
	auto data = static_cast<const CreUnit*>(msg);

	Vec2 pos(data->x(), data->y());

	auto unit = Unit::create(static_cast<Unit::UnitType>(data->type()), true);
	unit->setPosition(pos);
	unit->setTag(GameManager::getInstance()->_enemyTag++);

	MapLayer::getInstance()->addChild(unit);
}