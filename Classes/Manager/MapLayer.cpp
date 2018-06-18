#include"cocos2d.h"

#include"MapLayer.h"
#include"GameManager.h"
#include"UI/InfoBoard.h"

USING_NS_CC;

bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_bg = Sprite::create("map/map.png");
	_bg->setAnchorPoint(Vec2(0, 0));
	_bg->setPosition(Vec2(0, 0));

	addChild(_bg,-1);
	
	createWalls();

	/* 框选
	 * 初始大小为1000*1000
	 */
	//_select = Sprite::create("map/map.png");
	createSelectListener();

	return true;
}


MapLayer* MapLayer::getInstance()
{
	static MapLayer* _instance = MapLayer::create();

	return _instance;
}


void MapLayer::createWalls()
{
	auto pw1 = Sprite::create("map/wall_u.png");
	pw1->setAnchorPoint(Vec2(0, 1));
	pw1->setPosition(Vec2(130, 3200));
	auto pb1 = PhysicsBody::createBox(pw1->getContentSize());
	pb1->setDynamic(false);
	pw1->setPhysicsBody(pb1);
	this->addChild(pw1, -2);
	
	auto pw2 = Sprite::create("map/wall_u.png");
	pw2->setAnchorPoint(Vec2(0, 0));
	pw2->setPosition(Vec2(641, 0));
	auto pb2 = PhysicsBody::createBox(pw2->getContentSize());
	pb2->setDynamic(false);
	pw2->setPhysicsBody(pb2);
	this->addChild(pw2, -2);

	auto pw3 = Sprite::create("map/wall_l.png");
	pw3->setAnchorPoint(Vec2(0, 0));
	pw3->setPosition(Vec2(0, 0));
	auto pb3 = PhysicsBody::createBox(pw3->getContentSize());
	pb3->setDynamic(false);
	pw3->setPhysicsBody(pb3);
	this->addChild(pw3, -2);

	auto pw4 = Sprite::create("map/wall_l.png");
	pw4->setAnchorPoint(Vec2(0, 0));
	pw4->setPosition(Vec2(3071, 0));
	auto pb4 = PhysicsBody::createBox(pw4->getContentSize());
	pb4->setDynamic(false);
	pw4->setPhysicsBody(pb4);
	this->addChild(pw4, -2);

	auto pw5 = Sprite::create("map/wall_cl.png");
	pw5->setAnchorPoint(Vec2(0, 0));
	pw5->setPosition(Vec2(130, 1662));
	auto pb5 = PhysicsBody::createBox(pw5->getContentSize());
	pb5->setDynamic(false);
	pw5->setPhysicsBody(pb5);
	this->addChild(pw5, -2);

	auto pw6 = Sprite::create("map/wall_cl.png");
	pw6->setAnchorPoint(Vec2(0, 0));
	pw6->setPosition(Vec2(2806, 1184));
	auto pb6 = PhysicsBody::createBox(pw6->getContentSize());
	pb6->setDynamic(false);
	pw6->setPhysicsBody(pb6);
	this->addChild(pw6, -2);

	auto pw7 = Sprite::create("map/wall_c.png");
	pw7->setPosition(Vec2(1600, 1600));
	auto pb7 = PhysicsBody::createBox(pw7->getContentSize());
	pb7->setDynamic(false);
	pw7->setPhysicsBody(pb7);
	this->addChild(pw7, -2);

	auto pw8 = Sprite::create("map/wall_cu.png");
	pw8->setAnchorPoint(Vec2(0, 0));
	pw8->setPosition(Vec2(1020, 135));
	auto pb8 = PhysicsBody::createBox(pw8->getContentSize());
	pb8->setDynamic(false);
	pw8->setPhysicsBody(pb8);
	this->addChild(pw8, -2);

	auto pw9 = Sprite::create("map/wall_cu.png");
	pw9->setAnchorPoint(Vec2(0, 0));
	pw9->setPosition(Vec2(1024, 2816));
	auto pb9 = PhysicsBody::createBox(pw9->getContentSize());
	pb9->setDynamic(false);
	pw9->setPhysicsBody(pb9);
	this->addChild(pw9, -2);

}


void MapLayer::createSelectListener()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(false);
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		_touchBegin =_bg->convertToNodeSpace(touch->getLocation());
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		removeChildByTag(11);
		auto _select = Sprite::create("map/select.png");
		auto current = _bg->convertToNodeSpace(touch->getLocation());
		float scalex = current.x > _touchBegin.x ? (current.x - _touchBegin.x) : (_touchBegin.x - current.x);
		_select->setScaleX(scalex / 1000);
		float scaley = current.y > _touchBegin.y ? current.y - _touchBegin.y : _touchBegin.y - current.y;
		_select->setScaleY(scaley / 1000);
		_select->setPosition((current + _touchBegin) / 2);
		addChild(_select,1,11);
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto select = getChildByTag(11);
		if (select != nullptr)
		{
			auto _end = _bg->convertToNodeSpace(touch->getLocation());
			//auto rect = Rect(_touchBegin.x<_end.x?_touchBegin.x:_end.x, _touchBegin.y<_end.y?_touchBegin.y:_end.y,
				//_touchBegin.x>_end.x ? _touchBegin.x : _end.x, _touchBegin.y>_end.y ? _touchBegin.y : _end.y);   
			bool clear = true;

			for (auto iter : GameManager::getInstance()->_unitList)
			{
				auto pos = iter->getPosition();

				if ((pos.x > _touchBegin.x&&pos.x < _end.x) || (pos.x<_touchBegin.x&&pos.x>_end.x))
				{
					if ((pos.y > _touchBegin.y&&pos.y < _end.y) || (pos.y<_touchBegin.y&&pos.y>_end.y))
					{
						if (clear)
						{
							GameManager::getInstance()->clearSelectedBox();
							clear = false;
						}

						if(GameManager::getInstance()->_selectedBox.empty())
							InfoBoard::getInstance()->changeBoard(iter);
						GameManager::getInstance()->_selectedBox.push_back(iter);

						iter->setOpacity(180);
						iter->_isSelected = true;
					}
				}
			}
		}
		removeChildByTag(11);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}