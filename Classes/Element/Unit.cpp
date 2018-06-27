#include"Unit.h"
#include"Manager/GameManager.h"
#include"UI/InfoBoard.h"
#include"Manager/MapLayer.h"
#include"Network/MyGame_generated.h"

#include"cocos2d.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;

using namespace MyGame;

 Unit* Unit::create(UnitType type,bool isEnemy)
{
	 auto pUnit = new Unit;

	 pUnit->initUnit(type,isEnemy);

	 pUnit->createListener();
	 pUnit->createPhysics();

	 pUnit->_isSelected = false;
	 pUnit->_isEnemy = isEnemy;

	 //pUnit->autorelease();
	 
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

					 target->setSelected();
					 target->_isSelected = true;
				 }
				 
				 InfoBoard::getInstance()->changeBoard(this);
			 }
			 else
				 return;
		 }
		 else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT&&_isSelected)
		 {
			 Vec2 pos(this->getParent()->convertToNodeSpace(location));

			 target->move(pos);

			 GameManager::getInstance()->unitMove(this->getTag(), pos.x, pos.y);
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


 /**
 *各单位参数可以在这里设置
 */
 void Unit::initUnit(UnitType type,bool isEnemy)
 {
	 switch (type)
	 {
	 case UnitType::FAMER:
		 if (isEnemy)
			 this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/famer.jpg" : "Element/p/famer.jpg");
		 else
			 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/famer.jpg" : "Element/p/famer.jpg");
		 this->_type = UnitType::FAMER;
		 this->_attr = { 0,0.000002f,0. };
		 this->_health = 45;
		 this->_attackMode = false;
		 this->_status = Status::STAND;

		 break;

	 case UnitType::WARRIOR:
		 if (isEnemy)
			 this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/fighter.jpg" : "Element/p/fighter.jpg");
		 else
			 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/fighter.jpg" : "Element/p/fighter.jpg");
		 this->_type = UnitType::WARRIOR;
		 this->_attr = { 150,0.02f,256. };//////attack=6
		 this->_health = 45;
		 this->_attackMode = true;
		 this->_status = Status::STAND;

		 break;

	 case UnitType::TANK:
		 if (isEnemy)
			 this->initWithFile(GameManager::getInstance()->_enemyTeam ? "Element/t/warrior.jpg" : "Element/p/warrior.jpg");
		 else
			 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/warrior.jpg" : "Element/p/warrior.jpg");
		 this->_type = UnitType::TANK;
		 this->_attr = { 500,0.025f,256. };//////attack=3
		 this->_health = 125;
		 this->_attackMode = true;
		 this->_status = Status::STAND;

		 break;
	 }
 }


 void Unit::attack(Element* target)
 {
	 if (UserDefault::getInstance()->
		 getBoolForKey("Effect"))CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/electric.mp3");

	 auto damage = std::bind(&Element::getDamage, target, this->_attr.attack);
	 auto get = CallFunc::create(damage);

	 //攻击停顿 
	 this->stopActionsByFlags(1);

	 auto pos = target->getPosition();

	 float distance = this->getPosition().distance(pos);
	 
	 if (this->_type == Unit::UnitType::WARRIOR)
	 {
		 _bullet = Sprite::create("element/bullet/fighter/bullet1.png");
		 _bullet->setPosition(this->getPosition());
		 MapLayer::getInstance()->addChild(_bullet, 2);

		 auto move = MoveTo::create(distance*0.001, pos);

		 auto animation = Animation::create();
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet2.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet3.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet4.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet5.png");
		 animation->addSpriteFrameWithFile("element/bullet/fighter/bullet6.png");
		 animation->setLoops(1);
		 animation->setDelayPerUnit(0.07);

		 this->_attackAnima = Animate::create(animation);

		 auto remove = CallFunc::create(CC_CALLBACK_0(Unit::removeBullet, this));

		 auto sequence = Sequence::create(move, this->_attackAnima, get, remove, NULL);

		 _bullet->runAction(sequence);
	 }
	 else if (this->_type == Unit::UnitType::TANK)
	 {
		 _bullet = Sprite::create("element/bullet/warrior/bullet1.png");
		 _bullet->setPosition(this->getPosition());
		 MapLayer::getInstance()->addChild(_bullet, 2);

		 auto move = MoveTo::create(distance*0.001, pos);

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

		 this->_attackAnima = Animate::create(animation);

		 auto remove = CallFunc::create(CC_CALLBACK_0(Unit::removeBullet, this));

		 auto sequence = Sequence::create(move, this->_attackAnima, get, remove, NULL);

		 _bullet->runAction(sequence);
	 }
 }


 void Unit::removeBullet()
 {
	 //_bullet->stopAllActions();
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
				 this->attack(iter);

				 GameManager::getInstance()->unitAttack(this->getTag(), iter->getTag());
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


 /** 
 *在单位死亡后从_unitList删除
 */
 void Unit::die()
 {
	 if (!GameManager::getInstance()->_selectedBox.empty()&&GameManager::getInstance()->_selectedBox[0] == this)
	 {
		 GameManager::getInstance()->clearSelectedBox();

		 InfoBoard::getInstance()->clearBoard();
	 }
	 
	 if (this->_isEnemy)
	 {
		 GameManager::getInstance()->_enemyList.erase(this);
	 }
	 else
	 {
		 GameManager::getInstance()->_unitList.erase(this);
	 }
	 
	 MapLayer::getInstance()->removeChild(this);

	 //this->release();
 }


 void Unit::getDamage(unsigned damage)
 {
	 if (this->_health > 0)
	 {
		 this->_health -= damage;

		 if (!GameManager::getInstance()->_selectedBox.empty()&&GameManager::getInstance()->_selectedBox[0] == this)
		 {
			 InfoBoard::getInstance()->changeBoard(this);
		 }
	 
		 if (this->_health <= 0)
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

			 auto die = std::bind(&Unit::die, this);
			 auto godie = CallFunc::create(die);

			 auto sequence = Sequence::create(animate, godie, NULL);

			 this->stopAllActions();

			 this->runAction(sequence);
		 }
	 }
 }


 void Unit::move(Vec2 pos)
 {
	 this->stopActionsByFlags(1);

	 auto pMove = MoveTo::create(this->getPosition().distance(pos)*this->_attr.speed, pos);
	 pMove->setFlags(1);

	 this->runAction(pMove);
 }


 void Unit::setSelected()
 {
	 if (this->_isEnemy ? GameManager::getInstance()->_enemyTeam : GameManager::getInstance()->_team)
	 {
		 switch (this->_type)
		 {
		 case Unit::UnitType::FAMER:
			 this->setTexture("element/t/famerSelected.jpg");
			 break;
		 case Unit::UnitType::WARRIOR:
			 this->setTexture("element/t/fighterSelected.jpg");
			 break;
		 case Unit::UnitType::TANK:
			 this->setTexture("element/t/warriorSelected.jpg");
			 break;
		 }
	 }
	 else
	 {
		 switch (this->_type)
		 {
		 case Unit::UnitType::FAMER:
			 this->setTexture("element/p/famerSelected.jpg");
			 break;
		 case Unit::UnitType::WARRIOR:
			 this->setTexture("element/p/fighterSelected.jpg");
			 break;
		 case Unit::UnitType::TANK:
			 this->setTexture("element/p/warriorSelected.jpg");
			 break;
		 }
	 }
 }


 void Unit::unSelected()
 {
	 if (this->_isEnemy ? GameManager::getInstance()->_enemyTeam : GameManager::getInstance()->_team)
	 {
		 switch (this->_type)
		 {
		 case Unit::UnitType::FAMER:
			 this->setTexture("element/t/famer.jpg");
			 break;
		 case Unit::UnitType::WARRIOR:
			 this->setTexture("element/t/fighter.jpg");
			 break;
		 case Unit::UnitType::TANK:
			 this->setTexture("element/t/warrior.jpg");
			 break;
		 }
	 }
	 else
	 {
		 switch (this->_type)
		 {
		 case Unit::UnitType::FAMER:
			 this->setTexture("element/p/famer.jpg");
			 break;
		 case Unit::UnitType::WARRIOR:
			 this->setTexture("element/p/fighter.jpg");
			 break;
		 case Unit::UnitType::TANK:
			 this->setTexture("element/p/warrior.jpg");
			 break;
		 }
	 }
 }