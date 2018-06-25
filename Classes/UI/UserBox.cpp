#include "UserBox.h"

USING_NS_CC;

bool UserBox::init()
{
	this->initWithFile("roomScene/userBoxBg.png");          ////////////////////////////////////
	return true;
}


void UserBox::setTeam(bool team)
{
	_team = team;
	if (!teamPic)
	{
		teamPic = Sprite::create();
		teamPic->setPosition(cocos2d::Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.6f));
		addChild(teamPic, 1);
	}
	if (team)
		teamPic->setTexture("element/t/terran.png");
	else
		teamPic->setTexture("element/p/protoss.png");
}


void UserBox::setUserName(const std::string & name)
{
	this->name = name;
	if (!nameArea)
	{
		nameArea = ui::Text::create(name, "fonts/Maker Felt.ttf", 44);
		nameArea->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.1f));
		nameArea->setColor(Color3B::WHITE);
		nameArea->enableGlow(Color4B::BLACK);
		addChild(nameArea, 1);
	}
	else
	{
		nameArea->setString(name);
	}
}


void UserBox::setReadyLabel(bool ready)
{
	if (!readyLabel)
	{
		readyLabel = cocos2d::Label::createWithTTF("Ready!", "fonts/arial.ttf",40);
		readyLabel->setColor(cocos2d::Color3B::ORANGE);
		readyLabel->setPosition(this->getContentSize().width*0.7, this->getContentSize().height*0.9);
		readyLabel->setRotation(30);
		this->addChild(readyLabel, 2);
	}

	readyLabel->setVisible(ready);
}


bool UserBox::isUserReady()
{
	return readyLabel->isVisible();
}
