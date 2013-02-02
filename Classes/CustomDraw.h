#pragma once
#include"cocos2d.h"
class CustomDraw :
	public cocos2d::CCLayer
{
public:
	CustomDraw(void);
	~CustomDraw(void);
	void DrawLine(cocos2d::CCPoint start,cocos2d::CCPoint end,float width,cocos2d::ccColor4F col4f);
	void ClearLayer();
	virtual void draw();
	void CustomUpdate();
	float angle;
	float targetAngle;
	cocos2d::CCPoint touchPosBegin;
	
	cocos2d::CCProgressTimer*	life;
	cocos2d::CCProgressTimer*		cicle;
	cocos2d::CCProgressTimer*		cicleAng;
	float addPower;
	enum GameStatus
	{
		Init = 0,
		GetGameRandom,
		LineGame,
		AngelGame,	
		DirectionGame
	};
	enum SubStatus
	{
		Generate =0,
		Play,
		Submit
	};
	virtual bool					ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void					ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void					ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	float							CustomDraw::Lookat(cocos2d::CCPoint from,cocos2d::CCPoint to);

	double dotmultiply(cocos2d::CCPoint p1,cocos2d::CCPoint p2,cocos2d::CCPoint p0); 
	double relation(cocos2d::CCPoint start,cocos2d::CCPoint end,cocos2d::CCPoint p); 
	cocos2d::CCPoint  point2line(cocos2d::CCPoint start,cocos2d::CCPoint end,cocos2d::CCPoint point);
	cocos2d::CCPoint start;
	cocos2d::CCPoint end;
	cocos2d::CCPoint touchPos;
	cocos2d::CCPoint Target;
	
	cocos2d::CCSprite *midPointInfo;
	cocos2d::CCSprite *digreeInfo;


	std::string info;
	cocos2d::CCPoint scaleDown(cocos2d::CCPoint point);
	bool isTouched;
	SubStatus subStatus;
	float ccp2Angle(cocos2d::CCPoint from,cocos2d::CCPoint to);
	GameStatus curStatus;
	bool					switches[3];
};

