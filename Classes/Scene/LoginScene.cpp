#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include "LoginScene.h"
#include "StartScene.h"
#include "Manager/User.h"

USING_NS_CC;


Scene* LoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoginScene::create();

	scene->addChild(layer);

	return scene;
}


bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//==============create background=================
	auto pLoginBg = Sprite::create("background/LoginSceneBg.png");
	pLoginBg->setPosition(visibleSize / 2);
	addChild(pLoginBg);

	//==============play bgm===============
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/Torchlight.mp3", true);

	//==============effect music on================
	UserDefault::getInstance()->setBoolForKey("Effect", true);

	//==============login button================
	createLoginButton();

	//==============input box===============
	createInputBox();

	return true;
}


void LoginScene::createLoginButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto loginButton = ui::Button::create("icons/Button.png", "icons/ButtonSelected.png");
	loginButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.35f));
	loginButton->setOpacity(233);

	loginButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type==ui::Widget::TouchEventType::ENDED&&
			UserDefault::getInstance()->getBoolForKey("Effect"))
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/ButtonClick.mp3");
		

		if (type != ui::Widget::TouchEventType::ENDED) return;
		auto username = usernameInput->getString();
		if (username.empty())
		{
			MessageBox("Username can't be empty", "Alert");
		}
		else
		{
			username.substr(0, 16);
			UserDefault::getInstance()->setStringForKey("username", username);                                             
			User::getInstance()->setName(username);  

			Director::getInstance()->replaceScene(TransitionFade::create(1.2f, StartScene::createScene()));
		}
	});
	addChild(loginButton);
}


void LoginScene::createInputBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	usernameBg = Sprite::create("icons/input_normal.png");
	usernameBg->setScale(1.4f);
	usernameBg->setOpacity(128);

	usernameInput = ui::TextField::create("Input Username Here", "fonts/Quicksand-Bold.ttf", 28);     
	usernameInput->setString(UserDefault::getInstance()->getStringForKey("username", ""));
	usernameInput->setColor(Color3B::BLACK);
	usernameInput->setCursorChar('|');
	usernameInput->setCursorEnabled(true);
	usernameInput->setMaxLength(15);
	usernameInput->setMaxLengthEnabled(true);
	usernameInput->setPosition(usernameBg->getContentSize() / 2);
	usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

	usernameBg->addChild(usernameInput);

	usernameBg->setScale(1.5);
	usernameBg->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2 + usernameBg->getContentSize().height * 2));

	addChild(usernameBg);
}


void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
	switch (event)
	{
	case ui::TextField::EventType::ATTACH_WITH_IME:
		usernameBg->setTexture("icons/input_active.png");
		break;
	case ui::TextField::EventType::DETACH_WITH_IME:
		usernameBg->setTexture("icons/input_normal.png");
		break;
	}
}