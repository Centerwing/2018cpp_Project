#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoginScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	CREATE_FUNC(LoginScene);

private:
	void menuLoginCallback(cocos2d::Ref* pRef);

	void createLoginButton();
	void createInputBox();
	void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event);

	cocos2d::ui::TextField* usernameInput;
	cocos2d::Sprite* usernameBg;
};

















#endif // !_LOGINSCENE_H_