#include "TeamBox.h"

USING_NS_CC;

bool TeamBox::init()
{
	//auto bg = Sprite::create("RoomScene/teamBoxBg.png");
	//bg->setPosition(cocos2d::Vec2(42, 42));
	//addChild(bg, -1);

	if (this->_team == teamChoice::PROTOSS)
		this->initWithFile("RoomScene/p/famer.jpg");           
	else if (this->_team == teamChoice::TERRAN)
		this->initWithFile("RoomScene/t/famer.jpg");                 
	return true;
}

TeamBox * TeamBox::create(teamChoice team)
{
	auto teamBox = new (std::nothrow) TeamBox();
	if (teamBox) 
	{
		teamBox->_team = team;
		teamBox->init();
		teamBox->autorelease();
		return teamBox;
	}
	CC_SAFE_DELETE(teamBox);
	return nullptr;
}

void TeamBox::setChosen(bool choice)
{
	if (choice != isChosen) 
	{
		isChosen = choice;

		if (this->_team == teamChoice::PROTOSS)
		{
			if (isChosen)
				this->setTexture(Sprite::create("roomScene/p/famerl.jpg")
					->getTexture());
			else
				this->setTexture(Sprite::create("roomScene/p/famer.jpg")
					->getTexture());
		}
		else if (this->_team == teamChoice::TERRAN)
		{
			if (isChosen)
				this->setTexture(Sprite::create("roomScene/t/famerl.jpg")
					->getTexture());
			else
				this->setTexture(Sprite::create("roomScene/t/famer.jpg")
					->getTexture());
		}
	}
}

TeamBox::teamChoice TeamBox::getTeam()
{
	return _team;
}