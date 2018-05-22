#include"HelpScene.h"

#include"cocos2d.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
	auto pScene = Scene::create();

	auto pLayer = HelpScene::create();

	pScene->addChild(pLayer);

	return pScene;
}

bool HelpScene::init()
{

}