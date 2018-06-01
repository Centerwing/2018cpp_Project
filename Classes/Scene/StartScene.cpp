#include"StartScene.h"
#include"HelpScene.h"
#include"SettingScene.h"

#include"SimpleAudioEngine.h"

#include"cocos2d.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto pScene = Scene::create();

	auto pLayer = StartScene::create();

	pScene->addChild(pLayer);

	return pScene;
}

bool StartScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//===========================加入StartScene背景图片==================================
	auto pSprite = Sprite::create("background/StartSceneBg.png");
	pSprite->setPosition(visibleSize/2);
	addChild(pSprite,-1);

	//===========================加入菜单=======================
	auto pMenu = Menu::create();
	pMenu->setPosition(origin);

/*	//Play
	auto pMenuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(StartScene::menuPlayCallback, this));
	pMenuPlay->setColor(Color3B::BLACK);
	pMenuPlay->setPosition(visibleSize / 2);
	pMenu->addChild(pMenuPlay);
*/	
	//Setting
	auto pMenuSetting = MenuItemImage::create("icons/OptionButton.png", "icons/OptionButtonSelected.png", CC_CALLBACK_1(StartScene::menuSettingCallback, this));
	pMenuSetting->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 40);
	pMenu->addChild(pMenuSetting);

	//Help
	auto pMenuHelp = MenuItemImage::create("icons/HelpButton.png", "icons/HelpButtonSelected.png", CC_CALLBACK_1(StartScene::menuHelpCallback, this));
	pMenuHelp->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 120);
	pMenu->addChild(pMenuHelp);

	//Exit
	auto pMenuExit = MenuItemImage::create("icons/ExitButton.png", "icons/ExitButtonSelected.png", CC_CALLBACK_1(StartScene::menuExitCallback, this));
	pMenuExit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	pMenu->addChild(pMenuExit);

	addChild(pMenu);


	return true;
}


//Callback实现
/*void StartScene::menuPlayCallback(Ref*)
{
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.2f, RoomScene::createScene(),true));
}*/


void StartScene::menuSettingCallback(Ref*)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	Director::getInstance()->pushScene(TransitionFade::create(1.2f, SettingScene::createScene()));
}


void StartScene::menuHelpCallback(Ref*)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	Director::getInstance()->pushScene(TransitionFade::create(1.2f, HelpScene::createScene()));
}


void StartScene::menuExitCallback(Ref*)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	Director::getInstance()->end();

}
