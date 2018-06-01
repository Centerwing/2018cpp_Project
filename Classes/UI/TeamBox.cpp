#include "TeamBox.h"

bool TeamBox::init()
{
	auto bg = Sprite::create("RoomScene/teamBoxBg.png");
	bg->setPosition(cocos2d::Vec2(42, 42));
	addChild(bg, -1);

	if (this->_team == Team1)
		this->initWithFile("RoomScene/team1/unselected.png");                     /////////////////////////////
	else if (this->_team == Team2)
		this->initWithFile("RoomScene/team2/unselected.png");                    //////////////////////////////
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
			this->setTexture(cocos2d::Sprite::create("roomScene/team1/" + isChosen ? "selected.png" : "unselected.png")
			->getTexture());
	}
}

TeamBox::teamChoice TeamBox::getTeam()
{
	return _team;
}