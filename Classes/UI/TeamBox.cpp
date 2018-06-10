#include "TeamBox.h"

USING_NS_CC;

bool TeamBox::init()
{
	auto bg = Sprite::create("RoomScene/teamBoxBg.png");
	bg->setPosition(cocos2d::Vec2(42, 42));
	addChild(bg, -1);

	if (this->_team == Team1)
		this->initWithFile("RoomScene/team1/unSelected.png");           
	else if (this->_team == Team2)
		this->initWithFile("RoomScene/team2/unSelected.png");                 
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

		if (this->_team == Team1)
		{
			if (isChosen)
				this->setTexture(Sprite::create("roomScene/team1/selected.png")
					->getTexture());
			else
				this->setTexture(Sprite::create("roomScene/team1/unSelected.png")
					->getTexture());
		}
		else if (this->_team == Team2)
		{
			if (isChosen)
				this->setTexture(Sprite::create("roomScene/team2/selected.png")
					->getTexture());
			else
				this->setTexture(Sprite::create("roomScene/team2/unSelected.png")
					->getTexture());
		}
	}
}

TeamBox::teamChoice TeamBox::getTeam()
{
	return _team;
}