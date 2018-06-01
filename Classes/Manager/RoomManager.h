#ifndef _ROOMMANAGER_H_
#define _ROOMMANAGER_H_

#include"cocos2d.h"

#include"Network/Client.h"
#include"UI/UserBox.h"

class RoomManager : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RoomManager);

	cocos2d::Vector<UserBox*> userBoxes;

	void onUserChangeRole(int role);

	void onUserChangeStats(bool isReady);

	//void sendChat(const std::string& text);

private:
	Client* client;
	int gameStatus;

	void onEnter();
	void onExit();

	void onWelcome(const void* msg);

	void onRoomInfoUpdate(const void* msg);

	void onGameStatusChange(const void* msg);

	void onChat(const void* msg);
};

#endif
