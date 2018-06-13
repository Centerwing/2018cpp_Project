#include"Unit.h"
#include"Manager/GameManager.h"
#include"UI/InfoBoard.h"

#include"cocos2d.h"

USING_NS_CC;

 Unit* Unit::create(UnitType type,bool isEnemy)
{
	 auto pUnit = new Unit;

	 pUnit->initUnit(type);
	 pUnit->createListener();
	 pUnit->createPhysics();

	 pUnit->_isSelected = false;
	 pUnit->_attackMod = false;
	 pUnit->_isEnemy = isEnemy;

	 pUnit->autorelease();

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
				 GameManager::getInstance()->_selectedBox = target;

				 InfoBoard::getInstance()->changeBoard(this);

				 target->setOpacity(180);
				 target->_isSelected = true;
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


 void Unit::initUnit(UnitType type)
 {
	 switch (type)
	 {
	 case UnitType::FAMER:
		 this->initWithFile(GameManager::getInstance()->_team?"Element/t/famer.jpg":"Element/p/famer.jpg");         
		 this->_type = UnitType::FAMER;
		 this->_attr = { 45,0,0.000002f };
		 this->_status = Status::STAND;
		 GameManager::getInstance()->_money -= 50;
		 GameManager::getInstance()->_salary += 10;
		 break;

	 case UnitType::WARRIOR:
		 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/fighter.jpg" : "Element/p/fighter.jpg");
		 this->_type = UnitType::WARRIOR;
		 this->_attr = { 45,3,0.02f };
		 this->_status = Status::STAND;
		 GameManager::getInstance()->_money -= 75;
		 break;

	 case UnitType::TANK:
		 this->initWithFile(GameManager::getInstance()->_team ? "Element/t/warrior.jpg" : "Element/p/warrior.jpg");
		 this->_type = UnitType::TANK;
		 this->_attr = { 125,6,0.025f };
		 this->_status = Status::STAND;
		 GameManager::getInstance()->_money -= 125;
		 break;
	 }
 }