#ifndef _ROOMSCENE_H_
#define _ROOMSCENE_H_

#include "Manager/RoomManager.h"
#include "UI/TeamBox.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

class RoomScene: public cocos2d::Layer
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(RoomScene);

private:
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	//RoomManager* _roomManager;

	cocos2d::ui::Button * readyButton;
	cocos2d::Vector<TeamBox*> teamBoxes;

	bool isReady;

	std::function<void(bool)> readyButtonCallBack;
	std::function<void(int)> teamChangeCallback;

	void menuCloseCallback(cocos2d::Ref* pRef);

	void createUI();

	void createListener();

	void createReadyButton();



};

#endif

