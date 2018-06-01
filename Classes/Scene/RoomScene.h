#ifndef _ROOMSCENE_H_
#define _ROOMSCENE_H_

#include"cocos2d.h"



class RoomScene: public cocos2d::Layer
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(RoomScene);

private:
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	RoomManager * _roomManager;

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

