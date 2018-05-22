#ifndef _HELPSCENE_H_
#define _HELPSCENE_H_

#include"cocos2d.h"

class HelpScene :public cocos2d::Layer
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(HelpScene);

private:


};


#endif