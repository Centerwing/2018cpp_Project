#include"RoomManager.h"
#include"GameScene.h"                            //////////////////////////

#include "flatbuffers/flatbuffers.h"             //////////////////////////



USING_NS_CC;

bool RoomManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

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
	if (userBoxes.size() > 0)
	{
		// second enter room, request room info update
		flatbuffers::FlatBufferBuilder builder;
		auto orc = CreateRoomInfoUpdate(builder);
		auto msg = CreateMsg(builder, MsgType::MsgType_RoomInfoUpdate, orc.Union());
		builder.Finish(msg);
		client->send(builder.GetBufferPointer(), builder.GetSize());
	}
	CLIENT_ON(MsgType_Welcome, RoomController::onWelcome);
	CLIENT_ON(MsgType_RoomInfoUpdate, RoomController::onRoomInfoUpdate);
	CLIENT_ON(MsgType_GameStatusChange, RoomController::onGameStatusChange);
	CLIENT_ON(MsgType_Chat, RoomController::onChat);
#endif // NETWORK
}