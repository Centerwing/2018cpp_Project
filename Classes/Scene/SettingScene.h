#ifndef _SETTINGSCENE_H_
#define _SETTINGSCENE_H_

#include"cocos2d.h"

class SettingScene :public cocos2d::Layer
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(SettingScene);



	void menuCloseCallback(cocos2d::Ref* pRef);
	void menuBgMusicCallback(cocos2d::Ref* pRef);
	void menuEffectCallback(cocos2d::Ref* Ref);


};




#endif // !_SETTINGSCENE_H_

