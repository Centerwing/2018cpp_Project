#ifndef _ROOMMANAGER_H_
#define _ROOMMANAGER_H_

#include"cocos2d.h"

#include"Network/Client.h"

class RoomManager : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RoomManager);

private:
	Client* client;
	int gameStatus;


};




#endif
