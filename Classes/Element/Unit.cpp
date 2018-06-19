#include"Unit.h"
#include"Manager/GameManager.h"
#include"UI/InfoBoard.h"
#include"Manager/MapLayer.h"

#include"cocos2d.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;

 Unit* Unit::create(UnitType type,bool isEnemy)
{
	 auto pUnit = new Unit;

	 pUnit->initUnit(type);
	 pUnit->createListener();
	 pUnit->createPhysics();

	 pUnit->_isSelected = false;
	 pUnit->_isEnemy = isEnemy;

	 pUnit->autorelease();
	 
	 if (isEnemy)
		 GameManager::getInstance()->_enemyList.insert(pUnit);
	 else
		 GameManager::getInstance()->_unitList.insert(pUnit);

	 if (type != Unit::UnitType::FAMER&&!isEnemy)
	 {
		 pUnit->schedule(schedule_selector(Unit::attackUpdate), 1.5);
		 pUnit->_attackMode = true;
	 }
	 else
		 pUnit->_attackMode = false;

	 return pUnit;
}


 void Unit::createListener()
 {
	 auto pListener = EventListenerMouse::create();
	 pListener->onMouseDown = [=](EventMouse* event)
	 {
		 
		 Vec2 location = event->getLocationInView();
		 auto target = static_cast<Unit*>(event->getCurrentTarget());

		 if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		 { 
			 Vec2 locationInNode = target->convertToNodeSpace(location);
			 Size s = target->getContentSize();
			 Rect rect = Rect(0, 0, s.width, s.height);

			 if (rect.containsPoint(locationInNode))
			 {			
				 GameManager::getInstance()->clearSelectedBox();
				
				 if (!this->_isEnemy) 
				 {				 
					 GameManager::getInstance()->_selectedBox.push_back(target);

					 target->setOpacity(150);
					 target->_isSelected = true;
				 }
				 
				 InfoBoard::getInstance()->changeBoard(this);
			 }
			 else
				 return;
		 }
		 else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT&&_isSelected)
		 {
			 target->stopAllActions();

			 auto pMove = MoveTo::create(target->getParent()->convertToNodeSpace(location).distance(target->getPosition())*target->_attr.speed,
				 target->getParent()->convertToNodeSpace(location));
			 target->runAction(pMove);
		 }
		 
	 };

	 _eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
 }


 void Unit::createPhysics()
 {
	 PhysicsBody* pBody = PhysicsBody::createBox(this->getContentSize());
	 pBody->setGravityEnable(false);
	 pBody->setRotationEnable(false);

	 this->setPhysicsBody(pBody);
 }

 /*各单位参数可以在这里设置
  */
 void Unit::initUnit(UnitType type)
 {
	 switch (type)
	 {
	 case UnitType::FAMER:
		 this->initWithFile(GameManager::getInstance()->_team?"Element/t/famer.jpg":"Element/p/famer.jpg");         
		 this->_type = UnitType::FAMER;
		 this->_attr = { 0,0.000002f,0. };
		 this->_health = 45;
		 this->_attackMode = false;
		 this->_status = Status::STAND;

		 break;

	 case UnitType::WARRIOR:
		 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/fighter.jpg" : "Element/p/fighter.jpg");
		 this->_type = UnitType::WARRIOR;
		 this->_attr = { 15,0.02f,256. };//////attack=6
		 this->_health = 45;
		 this->_attackMode = true;
		 this->_status = Status::STAND;

		 break;

	 case UnitType::TANK:
		 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/warrior.jpg" : "Element/p/warrior.jpg");
		 this->_type = UnitType::TANK;
		 this->_attr = { 500,0.025f,256. };//////attack=3
		 this->_health = 125;
		 this->_attackMode = true;
		 this->_status = Status::STAND;

		 break;
	 }

	 this->_isSelected = false;
 }


 void Unit::attack(Vec2 target)
 {
	 float distance = this->getPosition().distance(target);
	 
	 if (this->_type == Unit::UnitType::WARRIOR)
	 {
		 _bullet = Sprite::create("element/bullet/fighter/bullet1.png");
		 _bullet->setPosition(this->getPosition());
		 MapLayer::getInstance()->addChild(_bullet, 2);

		 auto move = MoveTo::create(distance*0.001, target);
		 auto animation = Animation::create();
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet2.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet3.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet4.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet5.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet6.png");
		 animation->setLoops(1);
		 animation->setDelayPerUnit(0.07);

		 auto animate = Animate::create(animation);

		 auto remove = CallFunc::create(CC_CALLBACK_0(Unit::removeBullet, this));

		 auto sequence = Sequence::create(move, animate, remove, NULL);

		 _bullet->runAction(sequence);
	 }
	 else if (this->_type == Unit::UnitType::TANK)
	 {
		 _bullet = Sprite::create("element/bullet/warrior/bullet1.png");
		 _bullet->setPosition(this->getPosition());
		 MapLayer::getInstance()->addChild(_bullet, 2);

		 auto move = MoveTo::create(distance*0.001, target);
		 auto animation = Animation::create();
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet2.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet3.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet4.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet5.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet6.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet7.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet8.png");
		 animation->addSpriteFrameWithFile("element/bullet/warrior/bullet9.png");
		 animation->setLoops(1);
		 animation->setDelayPerUnit(0.04);

		 auto animate = Animate::create(animation);

		 auto remove = CallFunc::create(CC_CALLBACK_0(Unit::removeBullet, this));

		 auto sequence = Sequence::create(move, animate, remove, NULL);

		 _bullet->runAction(sequence);
	 }
 }


 void Unit::removeBullet()
 {
	 _bullet->stopAllActions();
	 MapLayer::getInstance()->removeChild(_bullet);
	 _bullet->release();
	 _bullet = nullptr;
 }


 void Unit::attackUpdate(float dt)
 {
	 if (this->_attackMode)
	 {
		 for (auto iter : GameManager::getInstance()->_enemyList)
		 {
			 if (this->getPosition().distance(iter->getPosition()) < this->_attr.range)
			 {
				 if (UserDefault::getInstance()->
					 getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/electric.mp3");
				 //攻击停顿
				 this->stopAllActions();
				 this->attack(iter->getPosition());
				 iter->getDamage(this->_attr.attack);
				 break;
			 }
		 }
	 }
 }


 /*void Unit::changeMode()
 {
	 this->_attackMode = !this->_attackMode;
	 if (this->_attackMode)
	 {
		 this->schedule(schedule_selector(Unit::attackUpdate), 1.5);
	 }
	 else
	 {
		 this->unschedule(schedule_selector(Unit::attackUpdate));
	 }
 }*/


 /* 
  * 在单位死亡后从_unitList删除
  */
 void Unit::die()
 {
	 MapLayer::getInstance()->removeChild(this);
	 if (this->_isEnemy)
	 {
		 GameManager::getInstance()->_enemyList.erase(this);
	 }
	 else
	 {
		 GameManager::getInstance()->_unitList.erase(this);
	 }
	 this->release();
 }


 void Unit::dying()
 {
	 auto animation = Animation::create();
	 animation->addSpriteFrameWithFile("element/die/unit/die1.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die2.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die3.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die4.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die5.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die6.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die7.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die8.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die9.png");
	 animation->addSpriteFrameWithFile("element/die/unit/die10.png");
	 animation->setLoops(1);
	 animation->setDelayPerUnit(0.04);

	 auto animate = Animate::create(animation);

	 auto todie = CallFunc::create(CC_CALLBACK_0(Unit::die, this));

	 auto sequence = Sequence::create(animate,todie, NULL);

	 this->runAction(sequence);
 }


 void Unit::getDamage(unsigned damage)
 {
	 this->_health -= damage;
	 if (this->_health < 0)
	 {
		 //死亡之后延迟播放动画，与被击中同步
		 auto delay = DelayTime::create(0.4);
		 auto dy = CallFunc::create(CC_CALLBACK_0(Unit::dying, this));
		 auto sequence = Sequence::create(delay, dy, NULL);

		 this->runAction(sequence);
	 }
 }