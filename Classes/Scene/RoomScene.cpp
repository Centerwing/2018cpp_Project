#include"RoomScene.h"
#include"Manager/RoomManager.h"
#include"UI/UserBox.h"
#include"UI/TeamBox.h"
#include"Network/Client.h"

#include"cocos2d.h"
#include"SimpleAudioEngine.h"


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

	//_roomManager = RoomManager::create();
	//addChild(_roomManager, 1);

	//readyButtonCallBack = CC_CALLBACK_1(RoomManager::onUserChangeStats, _roomManager);
	//teamChangeCallback = CC_CALLBACK_1(RoomManager::onUserChangeTeam, _roomManager);

	//addChild(_roomManager, -1);
	
	//==========create background=========
	auto pRoomBg = Sprite::create("background/RoomSceneBg.png");
	pRoomBg->setPosition(visibleSize/2);
	addChild(pRoomBg);

	createUI();
	//auto chatBox = ChatBox::create();

	return true;
}


void RoomScene::createUI()
{
	//============create userbox===========
	for (int i = 1; i < 3; i++) 
	{
		auto _userBox = UserBox::create();
		_userBox->setPosition(visibleSize.width/3*i,visibleSize.height*0.61f);
		addChild(_userBox);

		//roomManager->userBoxes.pushBack(_userBox);
	}


	//=============create teambox===============
	for (int i = 1; i < 3; ++i)
	{
		auto teamBox = TeamBox::create(static_cast<TeamBox::teamChoice>(i-1));
		teamBox->setPosition(Vec2(
			visibleSize.width * 0.6f + 2 * i * teamBox->getContentSize().width,
			visibleSize.height * 0.2f));
		addChild(teamBox);
		teamBoxes.pushBack(teamBox);
	}
	//default
	teamBoxes.at(0)->setChosen(true);


	//=============create listener===============
	createListener();


	//=============back button=============
	auto pBack = MenuItemImage::create("icons/help_back.png", "icons/help_backSelected.png", this, menu_selector(RoomScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(40, visibleSize.height - 40);
	addChild(pBackMenu);

	//=============ready button==============
	createReadyButton();

}


void RoomScene::createListener()
{
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch * touch, Event * event)
	{
		return true;
	};

	touchListener->onTouchEnded = [=](Touch * touch, Event * event) {
		auto point = touch->getLocation();
		for (auto pBox : teamBoxes)
		{
			auto range = pBox->getBoundingBox();

			if (range.containsPoint(point))
			{
				teamChangeCallback(pBox->getTeam());

				for (auto val : teamBoxes)
					val->setChosen(false);

				pBox->setChosen(true);
				break;
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto keyEventListener = EventListenerKeyboard::create();
	keyEventListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event)
	{
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->popScene();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyEventListener, this);
}


void RoomScene::createReadyButton()
{
	auto getShowText = [](bool isReady)
	{
		return isReady ? "Cancel" : "Ready";
	};
	readyButton = ui::Button::create("icons/Button.png", "icons/ButtonSelected.png");
	readyButton->setTitleText(getShowText(isReady));
	readyButton->setTitleFontSize(32);

	readyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto button = static_cast<ui::Button*>(sender);
			isReady = !isReady;
			button->setTitleText(getShowText(isReady));
			if (readyButtonCallBack) readyButtonCallBack(isReady);
		}
	});

	readyButton->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.1f) + origin);
	this->addChild(readyButton);
}


void RoomScene::menuCloseCallback(Ref* pRef)
{
	if (UserDefault::getInstance()->
		getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

	Client::getInstance()->close();
	Director::getInstance()->popScene();
}