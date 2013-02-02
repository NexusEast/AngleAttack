#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class CustomDraw;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend to return the exactly class pointer
    static cocos2d::CCScene* scene(); 
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void LineDectectCallback(CCObject* pSender);
	void AngleJudgeCallback(CCObject* pSender);
	void DirectionJudgeCallback(CCObject* pSender);
	void OKCallback(CCObject* pSender);
	static cocos2d::CCPoint	scaleRatio;
	CustomDraw				*customDraw;
	cocos2d::CCLabelTTF* timer ;//= CCLabelTTF::create("Dev Mode", "Arial", 24);
	cocos2d::CCLabelTTF* angler ;//= CCLabelTTF::create("Dev Mode", "Arial", 24);
	cocos2d::CCLabelTTF* pLabel ;
	float totalTime;
	cocos2d::CCSprite*		BG;
	cocos2d::CCSprite*		on;
	cocos2d::CCSprite*		off;
	cocos2d::CCSprite*		ok;
	cocos2d::CCSprite*		ok_down;
	cocos2d::CCSprite*		pwr;
	cocos2d::CCSprite*		rpanel;
	cocos2d::CCSprite*		rect;
	cocos2d::CCMenu			*LineDectect;
	cocos2d::CCMenu			*AngleJudge;
	cocos2d::CCMenu			*DirectionJudge;
	cocos2d::CCMenu			*confirm;
	cocos2d::CCMenu			*setToggleMenu(const char* on,const char* off,cocos2d::CCPoint pos,cocos2d::SEL_MenuHandler callBack,int setIndex);
	void					Update(float dt);
	float			power;

	
    LAYER_CREATE_FUNC(HelloWorld);
};
 
#endif  // __HELLOWORLD_SCENE_H__