#ifndef _SETTINGSCENE_H_
#define _SETTINGSCENE_H_

#include"cocos2d.h"

class SettingScene :public cocos2d::Layer
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(SettingScene);


	//void stopMusic();

	void menuCloseCallback(cocos2d::Ref* pRef);
	void menuBgMusicCallback(cocos2d::Ref* pRef);

	//void onEnter();
};




#endif // !_SETTINGSCENE_H_

