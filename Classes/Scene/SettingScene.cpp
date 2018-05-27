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


	auto pSettingBg = Sprite::create("Background/SettingSceneBg.jpg");
	pSettingBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(pSettingBg, -1);

	//BgMusic button
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




	//back
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(SettingScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	addChild(pBackMenu);


	return true;
}




//BgMusicCallback
void SettingScene::menuBgMusicCallback(Ref* pRef)
{
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


void SettingScene::menuCloseCallback(Ref* Ref)
{
	Director::getInstance()->popScene();
}