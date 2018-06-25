#ifndef _USERBOX_H_
#define _USERBOX_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UserBox : public cocos2d::Sprite {
public:

	virtual bool init();
	CREATE_FUNC(UserBox);

	void setTeam(bool team);

	void setUserName(const std::string& name);

	void setReadyLabel(bool ready);

	bool isUserReady();

private:
	bool _team;
	cocos2d::Sprite* teamPic = nullptr;
	cocos2d::Label* readyLabel = nullptr;

	std::string name;
	cocos2d::ui::Text * nameArea;

};


#endif // !_USERBOX_H_
