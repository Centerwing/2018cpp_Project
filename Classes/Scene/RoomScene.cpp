#include"RoomScene.h"
#include"Manager/RoomManager.h"
#include"UI/UserBox.h"
#include"UI/TeamBox.h"
#include"GameScene.h"
#include"Element/User.h"
#include"UI/ChatBox.h"

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

	_roomManager = RoomManager::create();
	addChild(_roomManager, -1);

	readyButtonCallBack = CC_CALLBACK_1(RoomManager::ChangeStats, _roomManager);
	teamChangeCallback = CC_CALLBACK_1(RoomManager::ChangeTeam, _roomManager);

	
	//==========create background=========
	auto pRoomBg = Sprite::create("background/RoomSceneBg.jpg");
	pRoomBg->setPosition(visibleSize/2);
	addChild(pRoomBg);

	createUI();

	auto chatBox = ChatBox::create();
	chatBox->sendText = CC_CALLBACK_1(RoomManager::sendChat, _roomManager);
	chatBox->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.15f);
	addChild(chatBox);

	isReady = false;
	User::getInstance()->_ready = false;

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

		_roomManager->userBoxes.push_back(_userBox);
	}
	//default
	_roomManager->userBoxes[0]->setUserName(User::getInstance()->getName());
	_roomManager->userBoxes[0]->setTeam(true);
	_roomManager->userBoxes[0]->setReadyLabel(false);

	_roomManager->userBoxes[1]->setReadyLabel(false);

	//=============create teambox===============
	for (int i = 1; i < 3; ++i)
	{
		auto teamBox = TeamBox::create(static_cast<TeamBox::teamChoice>(i-1));
		teamBox->setPosition(Vec2(
			visibleSize.width * 0.65f + 2 * i * teamBox->getContentSize().width,
			visibleSize.height * 0.11f));
		addChild(teamBox);
		teamBoxes.pushBack(teamBox);
	}
	//default
	teamBoxes.at(1)->setChosen(true);
	User::getInstance()->_team = true;


	createListener();


	//=============back button=============
	auto pBack = MenuItemImage::create("icons/Back.png", "icons/BackSelected.png", this, menu_selector(RoomScene::menuCloseCallback));
	auto pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(64, visibleSize.height - 40);
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
				if (UserDefault::getInstance()->
					getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

				//GameManager::getInstance()->_team = (pBox->getTeam() == TeamBox::teamChoice::TERRAN);//这里不能用GameManager
				User::getInstance()->_team = (pBox->getTeam() == TeamBox::teamChoice::TERRAN);
				teamChangeCallback(static_cast<bool>(pBox->getTeam()));

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
	readyButton = ui::Button::create("RoomScene/ReadyButton.png", "RoomScene/ReadyButtonSelected.png");
	readyButton->setTitleText(getShowText(isReady));
	readyButton->setTitleFontSize(34);

	readyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (UserDefault::getInstance()->
				getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");

			auto button = static_cast<ui::Button*>(sender);
			isReady = !isReady;
			User::getInstance()->_ready = isReady;
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

	Director::getInstance()->popScene();
}