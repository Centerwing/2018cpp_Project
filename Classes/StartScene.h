#ifndef _STARTSCENE_H_
#define _STARTSCENE_H_

#include"cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(StartScene);

private:
	void menuPlayCallback(Ref* pRef);
	void menuSettingCallback(Ref* pRef);
	void menuHelpCallback(Ref* pRef);
	void menuExitCallback(Ref* pRef);

	void onEnter();
};

#endif