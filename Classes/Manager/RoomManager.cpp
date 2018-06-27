#include"RoomManager.h"
#include"Scene/GameScene.h"        
#include"Network/MyGame_generated.h"
#include"Element/User.h"

#include "flatbuffers/flatbuffers.h"           

using namespace MyGame;
USING_NS_CC;

bool RoomManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//default
	_roomNumber = 0;

	return true;
}


void RoomManager::onEnter()
{
	gameStatus = 0;
	Layer::onEnter();
#ifdef NETWORK
	client = Client::getInstance();
	if (!client->isConnected())
	{
		client->connect();
	}

	//等待连接服务器后再执行发送Join信息的代码
	while (!client->isConnected());

	flatbuffers::FlatBufferBuilder builder;
	auto name = builder.CreateString(User::getInstance()->getName());
	auto info = CreateJoin(builder,name);
	MsgBuilder msg(builder);
	msg.add_data(info.Union());
	msg.add_type(MsgType::MsgType_Join);
	msg.add_data_type(Info_Join);
	auto ms = msg.Finish();
	builder.Finish(ms);
	client->send(builder.GetBufferPointer(), builder.GetSize());
	
	CLIENT_ON(MsgType_Welcome, RoomManager::onWelcome);
	CLIENT_ON(MsgType_Join, RoomManager::onJoin);
	CLIENT_ON(MsgType_ChangeStatus, RoomManager::onChangeStatus);
	CLIENT_ON(MsgType_ChangeTeam, RoomManager::onChangeTeam);
	CLIENT_ON(MsgType_Chat, RoomManager::onChat);
	//CLIENT_ON(MsgType_GameStart, RoomManager::onGameStart);
#endif // NETWORK
}


void RoomManager::onExit()
{
	/*
#ifdef NETWORK
	if (gameStatus == 0) // player exit room directly
	{
		client->close();
	}
	client->clear();
	client = nullptr;
#endif // NETWORK
    */
	Layer::onExit();
}


void RoomManager::ChangeTeam(bool team)
{
	userBoxes[_roomNumber]->setName(User::getInstance()->getName());
	userBoxes[_roomNumber]->setTeam(team);

	flatbuffers::FlatBufferBuilder builder;
	auto info = CreateChangeTeam(builder, team);
	MsgBuilder msg(builder);
	msg.add_type(MsgType::MsgType_ChangeTeam);
	msg.add_data_type(Info_ChangeTeam);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);
	client->send(builder.GetBufferPointer(), builder.GetSize());
}


void RoomManager::ChangeStats(bool ready)
{
	userBoxes[_roomNumber]->setReadyLabel(ready);

	flatbuffers::FlatBufferBuilder builder;
	auto info = CreateChangeStatus(builder, ready);
	MsgBuilder msg(builder);
	msg.add_type(MsgType::MsgType_ChangeStatus);
	msg.add_data_type(Info_ChangeStatus);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);
	client->send(builder.GetBufferPointer(), builder.GetSize());

	//判断是否房间内的玩家都在准备状态
	if (ready&&userBoxes[1 - _roomNumber]->isUserReady())
	{
		//游戏开始
		User::getInstance()->_roomNumber = _roomNumber;
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, GameScene::createScene()));
	}
}


//收到Join信息说明你是第一个进房间的
void RoomManager::onJoin(const void* msg)
{
	auto data = static_cast<const Join*>(msg);
	userBoxes[1]->setUserName(data->name()->str());
	//default
	userBoxes[1]->setTeam(true);
	userBoxes[1]->setReadyLabel(false);
	User::getInstance()->_enemyTeam = true;

	//回复一个welcome信息
	flatbuffers::FlatBufferBuilder builder;
	auto name = builder.CreateString(User::getInstance()->getName());
	auto info = CreateWelcome(builder, name, User::getInstance()->_team, User::getInstance()->_ready);
	MsgBuilder msger(builder);
	msger.add_type(MsgType_Welcome);
	msger.add_data_type(Info_Welcome);
	msger.add_data(info.Union());
	auto orc = msger.Finish();
	builder.Finish(orc);
	client->send(builder.GetBufferPointer(), builder.GetSize());
}


//收到Welcome信息说明你是第二个进房间的
void RoomManager::onWelcome(const void* msg)
{
	userBoxes[1]->setUserName(User::getInstance()->getName());
	userBoxes[1]->setTeam(true);
	userBoxes[1]->setReadyLabel(false);

	_roomNumber = 1;

	auto data = static_cast<const Welcome*>(msg);

	userBoxes[0]->setUserName(data->name()->str());
	userBoxes[0]->setTeam(data->team());
	userBoxes[0]->setReadyLabel(data->ready());
	
	User::getInstance()->_enemyTeam = data->team();
}


void RoomManager::onChangeTeam(const void* msg)
{
	auto data = static_cast<const MyGame::ChangeTeam*>(msg);

	userBoxes[1 - _roomNumber]->setTeam(data->team());
	User::getInstance()->_enemyTeam = data->team();
}


void RoomManager::onChangeStatus(const void* msg)
{
	auto data = static_cast<const MyGame::ChangeStatus*>(msg);

	userBoxes[1 - _roomNumber]->setReadyLabel(data->ready());

	//判断是否房间内的玩家都在准备状态
	if (User::getInstance()->_ready&&data->ready())
	{
		//游戏开始
		User::getInstance()->_roomNumber = _roomNumber;
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, GameScene::createScene()));
	}
}


void RoomManager::onChat(const void * msg)
{
	auto data = static_cast<const Chat*>(msg);
	getParent()->getEventDispatcher()->dispatchCustomEvent("update_chat", const_cast<char *>(data->chat()->c_str()));
}


void RoomManager::sendChat(const std::string & text)
{
	flatbuffers::FlatBufferBuilder builder;
	auto str = builder.CreateString(text);
	auto info = CreateChat(builder, str);
	MsgBuilder msg(builder);
	msg.add_type(MsgType_Chat);
	msg.add_data_type(Info_Chat);
	msg.add_data(info.Union());
	auto orc = msg.Finish();
	builder.Finish(orc);

	getParent()->getEventDispatcher()->dispatchCustomEvent("update_chat",const_cast<char *>( text.c_str()));
	client->send(builder.GetBufferPointer(), builder.GetSize());
}

