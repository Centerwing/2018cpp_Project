#include"GameManager.h"
#include"Element/User.h"

#include"cocos2d.h"

USING_NS_CC;

bool GameManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//_selectedBox = nullptr;
	_team = User::getInstance()->_team;

	schedule(schedule_selector(GameManager::salaryUpdate), 5.0f);
	
	return true;
}


GameManager* GameManager::getInstance()
{
	static GameManager* _instance = GameManager::create();

	return _instance;
}


void GameManager::clearSelectedBox()
{

	/*if (_selectedBox != nullptr)
	{
		_selectedBox->_isSelected = false;
		_selectedBox->setOpacity(255);
	}

	_selectedBox = nullptr;*/
	for (auto iter : _selectedBox)
	{
		iter->_isSelected = false;
		iter->setOpacity(255);
	}
	_selectedBox.clear();
}


void GameManager::salaryUpdate(float dt)
{
	_money += _salary;
}