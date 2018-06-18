#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include"cocos2d.h"

USING_NS_CC;

class MapLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(MapLayer);

	static MapLayer* getInstance();
	void operator=(MapLayer const &) = delete;

	Vec2 _touchBegin;
	
private:
	void createWalls();

	void createSelectListener();

	Sprite* _bg;

};

#endif // !_MAPLAYER_H_

