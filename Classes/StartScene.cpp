#include"StartScene.h"
#include"HelpScene.h"

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


	//加入StartScene背景图片
	auto pSprite = Sprite::create("StartBackground.jpg");
	pSprite->setPosition(visibleSize/2);
	addChild(pSprite,-1);

	//加入菜单
	auto pMenu = Menu::create();
	pMenu->setPosition(origin);

	//Play
	auto pMenuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(StartScene::menuPlayCallback, this));
	pMenuPlay->setColor(Color3B::BLACK);
	pMenuPlay->setPosition(visibleSize / 2);
	pMenu->addChild(pMenuPlay);

	//Setting
	auto pMenuSetting = MenuItemFont::create("Setting", CC_CALLBACK_1(StartScene::menuSettingCallback, this));
	pMenuSetting->setColor(Color3B::BLACK);
	pMenuSetting->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	pMenu->addChild(pMenuSetting);
	
	//Help
	auto pMenuHelp = MenuItemFont::create("Help", CC_CALLBACK_1(StartScene::menuHelpCallback, this));
	pMenuHelp->setColor(Color3B::BLACK);
	pMenuHelp->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	pMenu->addChild(pMenuHelp);

	//Exit
	auto pMenuExit = MenuItemFont::create("Exit", CC_CALLBACK_1(StartScene::menuExitCallback, this));
	pMenuExit->setColor(Color3B::BLACK);
	pMenuExit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);
	pMenu->addChild(pMenuExit);

	addChild(pMenu);

	return true;
}

// music
void StartScene::onEnter()
{
	Scene::onEnter();
	//
}

//Callback实现
void StartScene::menuPlayCallback(Ref*)
{
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.0f, RoomScene::createScene()));
}


void StartScene::menuSettingCallback(Ref*)
{
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.0f, SettingScene::createScene()));
}


void StartScene::menuHelpCallback(Ref*)
{
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.0f, HelpScene::createScene()));
}


void StartScene::menuExitCallback(Ref*)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
