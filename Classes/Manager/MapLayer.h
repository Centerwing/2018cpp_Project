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
private:
	void createWalls();
};

#endif // !_MAPLAYER_H_

