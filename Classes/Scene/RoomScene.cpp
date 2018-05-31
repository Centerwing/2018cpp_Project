#include"RoomScene.h"

#include"cocos2d.h"


USING_NS_CC;


Scene* RoomScene::createScene()
{
	auto pScene = Scene::create();

	auto pLayer = RoomScene::create();

	pScene->addChild(pLayer);

	return pScene;
}


bool RoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	_roomManager = RoomManager::create();

	readyButtonCallBack = CC_CALLBACK_1(RoomManager::onUserChangeStats, _roomManager);
	teamChangeCallback = CC_CALLBACK_1(RoomManager::onUserChangeRole, _roomManager);

	addChild(_roomManager, -1);

	//==========create background=========
	auto pRoomBg = Sprite::create("background/RoomSceneBg.jpg");
	pRoomBg->setPosition(visibleSize/2);

	//auto chatBox = ChatBox::create();

	return true;
}


void RoomScene::createUI()
{

}