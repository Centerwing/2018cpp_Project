#ifndef _TEAMBOX_H_
#define _TEAMBOX_H_


#include"cocos2d.h"

class TeamBox : public cocos2d::Sprite
{
public:

	enum teamChoice
	{
		Team1,
		Team2
	};

	virtual bool init();
	static TeamBox* create(teamChoice team);

	void setChosen(bool choice);
	teamChoice getTeam();

private:
	bool isChosen = false;
	teamChoice _team;
};

#endif // !_TEAMBOX_H_
