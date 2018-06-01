#include"SettingScene.h"
#include"SimpleAudioEngine.h"

#include"cocos2d.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
	auto pScene = Scene::create();

	auto pLayer = SettingScene::create();

	pScene->addChild(pLayer);

	return pScene;
}


bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto pSettingBg = Sprite::create("background/SettingSceneBg.jpg");
	pSettingBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(pSettingBg, -1);

	//=================BgMusic button=================
	auto pBgMusicOn = Sprite::create("icons/BgMusicOn.png");
	auto pBgMusicOff = Sprite::create("icons/BgMusicOff.png");

	auto pMenuMusicOn = MenuItemSprite::create(pBgMusicOn,pBgMusicOn);
	auto pMenuMusicOff = MenuItemSprite::create(pBgMusicOff, pBgMusicOff);

	auto pMusicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuBgMusicCallback, this), pMenuMusicOff, pMenuMusicOn, nullptr);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		pMusicToggle->setSelectedIndex(1);
	}
	else
	{
		pMusicToggle->setSelectedIndex(0);
	}

	auto pBgMenu = Menu::create(pMusicToggle, nullptr);
	pBgMenu->setPosition(visibleSize.width / 2 + 150, visibleSize.height / 2);
	this->addChild(pBgMenu);


	//===================effect music button==================
	auto pEffectOn = Sprite::create("icons/BgMusicOn.png");
	auto pEffectOff = Sprite::create("icons/BgMusicOff.png");

	auto pMenuEffectOn = MenuItemSprite::create(pEffectOn, pEffectOn);
	auto pMenuEffectOff = MenuItemSprite::create(pEffectOff, pEffectOff);

	auto pEffectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuEffectCallback, this), pMenuEffectOff, pMenuEffectOn, nullptr);
	if (UserDefault::getInstance()->getBoolForKey("Effect"))
	{
		pEffectToggle->setSelectedIndex(1);
	}
	else
	{
		pEffectToggle->setSelectedIndex(0);
	}

	auto pEffectMenu = Menu::create(pEffectToggle, nullptr);
	pEffectMenu->setPosition(visibleSize.width / 2 + 150, visibleSize.height / 2-50);
	this->addChild(pEffectMenu);


	//========================back=========================
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(SettingScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	addChild(pBackMenu);


	return true;
}




void SettingScene::menuBgMusicCallback(Ref* pRef)
{
	if(UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	auto pBgMusic = dynamic_cast<MenuItemToggle*>(pRef);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		pBgMusic->setSelectedIndex(0);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		pBgMusic->setSelectedIndex(1);
	}
}



void SettingScene::menuEffectCallback(Ref* pRef)
{

	auto pEffectMusic = dynamic_cast<MenuItemToggle*>(pRef);
	if (UserDefault::getInstance()->getBoolForKey("Effect"))
	{
		UserDefault::getInstance()->setBoolForKey("Effect", false);
		pEffectMusic->setSelectedIndex(0);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

		UserDefault::getInstance()->setBoolForKey("Effect", true);
		pEffectMusic->setSelectedIndex(1);
	}
}
void SettingScene::menuCloseCallback(Ref* Ref)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	Director::getInstance()->popScene();
}