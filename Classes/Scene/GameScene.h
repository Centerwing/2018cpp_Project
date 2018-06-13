#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include"cocos2d.h"
#include<vector>

#include"Element/Unit.h"
#include"Element/Building.h"
#include"Manager/GameManager.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
	
	void MapMoveUpdate(float dt);

private:
	//void onEnter();
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	/*Z-Order
	* _infoBoard = 2
	* _map = 1
	* _manager = -1
	*/
	cocos2d::Layer* _map;
	cocos2d::Layer* _manager;
	cocos2d::Layer* _infoBoard;

	void createMap();
	void createManager();
	void createInfoBoard();

	void initGame();

	void createMouseListener();
	
};


#endif // !_GAMESCENE_H_

