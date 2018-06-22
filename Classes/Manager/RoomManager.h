#ifndef _ROOMMANAGER_H_
#define _ROOMMANAGER_H_

#include"cocos2d.h"
#include<vector>

#include"Network/Client.h"
#include"UI/UserBox.h"

class RoomManager : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RoomManager);

	std::vector<UserBox*> userBoxes;

	void ChangeTeam(bool team);

	void ChangeStats(bool ready);
	
	void sendChat(const std::string & text);

	int _roomNumber;

	//void sendChat(const std::string& text);

private:
	Client* client;
	int gameStatus;

	void onEnter();
	void onExit();

	void onWelcome(const void* msg);

	void onJoin(const void* msg);

	void onChangeTeam(const void* msg);

	void onChangeStatus(const void* msg);

	void onChat(const void* msg);
};

#endif