#include"HelpScene.h"
#include"SimpleAudioEngine.h"

#include"cocos2d.h"

USING_NS_CC;


Scene* HelpScene::createScene()
{
	auto pScene = Scene::create();

	auto pLayer = HelpScene::create();

	pScene->addChild(pLayer);

	return pScene;
}



bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	auto pHelpBg1 = Sprite::create("HelpSceneBg1.jpg");
	pHelpBg1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(pHelpBg1, -1);

	//next
	auto pNext = MenuItemImage::create("icons/help_next.png", "icons/help_nextSelected.png", this, menu_selector(HelpScene::menuNextCallback));
	auto pNextMenu = Menu::create(pNext, NULL);
	pNextMenu->setPosition(visibleSize.width - 40, visibleSize.height / 2);
	addChild(pNextMenu);

	//back
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(HelpScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	addChild(pBackMenu);




	return true;
}





void HelpScene::createHelpBg1()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pScene = Scene::create();
	auto pLayer = Layer::create();
	pScene->addChild(pLayer);


	auto pHelpBg1 = Sprite::create("HelpSceneBg1.jpg");
	pHelpBg1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pLayer->addChild(pHelpBg1, -1);

	//next
	auto pNext = MenuItemImage::create("icons/help_next.png", "icons/help_nextSelected.png", this, menu_selector(HelpScene::menuNextCallback));
	auto pNextMenu = Menu::create(pNext, NULL);
	pNextMenu->setPosition(visibleSize.width - 40, visibleSize.height / 2);
	pLayer->addChild(pNextMenu);

	//back
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(HelpScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	pLayer->addChild(pBackMenu);


	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f, pScene, true));
}


void HelpScene::createHelpBg2()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pScene = Scene::create();
	auto pLayer = Layer::create();
	pScene->addChild(pLayer);


	auto pHelpBg2 = Sprite::create("HelpSceneBg2.jpg");
	pHelpBg2->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pLayer->addChild(pHelpBg2, -1);

	//last
	auto pLast = MenuItemImage::create("icons/help_last.png", "icons/help_lastSelected.png", this, menu_selector(HelpScene::menuLastCallback));
	auto pLastMenu = Menu::create(pLast, NULL);
	pLastMenu->setPosition(40, visibleSize.height / 2);
	pLayer->addChild(pLastMenu);


	//back
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(HelpScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	pLayer->addChild(pBackMenu);

	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f, pScene, false));
}




void HelpScene::menuNextCallback(Ref* pRef)
{
	HelpScene::createHelpBg2();
}

void HelpScene::menuLastCallback(Ref* pRef)
{
	HelpScene::createHelpBg1();
}

void HelpScene::menuCloseCallback(Ref* Ref)
{
	Director::getInstance()->popScene();
}