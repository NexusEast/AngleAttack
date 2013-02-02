#include "HelloWorldScene.h"

#include "CustomDraw.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene); 
        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
		layer->customDraw = new CustomDraw();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
		scene->addChild(layer->customDraw);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
		scaleRatio.x = CCDirector::sharedDirector()->getWinSizeInPixels().width/1920;
		scaleRatio.y = CCDirector::sharedDirector()->getWinSizeInPixels().height/1080;


		
			BG  = CCSprite::create("BG.png");
		//	cicle= CCSprite::create("cicle.png");
			on= CCSprite::create("ON.png");
			off= CCSprite::create("OFF.png");
			ok= CCSprite::create("ok.png");
			ok_down= CCSprite::create("ok-down.png");
			pwr= CCSprite::create("PWR.png");
			rpanel= CCSprite::create("rpanel.png");
			rect= CCSprite::create("rect.png");

			totalTime = 0;


			



			BG->setScaleX(scaleRatio.x);
			BG->setScaleY(scaleRatio.y);
			BG->setAnchorPoint(ccp(0,0));
			//BG->setVisible(false);
			this->addChild(BG);
			 
			
			on->setScaleX(scaleRatio.x);
			on->setScaleY(scaleRatio.y);
			
			off->setScaleX(scaleRatio.x);
			off->setScaleY(scaleRatio.y);
			
			ok->setScaleX(scaleRatio.x);
			ok->setScaleY(scaleRatio.y);
			
			ok_down->setScaleX(scaleRatio.x);
			ok_down->setScaleY(scaleRatio.y);
			
			pwr->setScaleX(scaleRatio.x);
			pwr->setScaleY(scaleRatio.y);
			
			rpanel->setScaleX(scaleRatio.x);
			rpanel->setScaleY(scaleRatio.y);
			rpanel->setAnchorPoint(ccp(1,0));
			rpanel->setPositionX(CCDirector::sharedDirector()->getWinSizeInPixels().width);
			this->addChild(rpanel);

			rect->setScaleX(scaleRatio.x);
			rect->setScaleY(scaleRatio.y);


			
			power = 0;





		


		





			
			CCMenuItemToggle *pLineDectectTogg = CCMenuItemToggle::create(this, menu_selector(HelloWorld::LineDectectCallback) ,
		CCMenuItemImage::create("OFF.png",
		"OFF.png"),
	
		CCMenuItemImage::create("ON.png",
		"ON.png"),NULL);

			CCMenuItemImage *okk = 
				CCMenuItemImage ::create("ok.png","ok-down.png",
				this,menu_selector(HelloWorld::OKCallback));
			okk->setPosition(ccp(1308.5*scaleRatio.x,75.8*scaleRatio.y));
			okk->setScaleX(scaleRatio.x);
			okk->setScaleY(scaleRatio.y); 
			confirm=CCMenu::create(okk , NULL);
			confirm->setPosition(ccp(0,0));
		//	confirm->setAnchorPoint(ccp(0,0));
			this->addChild(confirm);



			pLineDectectTogg->setScaleX(scaleRatio.x);
			pLineDectectTogg->setScaleY(scaleRatio.y);
			pLineDectectTogg->setPosition(ccp(1581.35*scaleRatio.x,1012*scaleRatio.y));
			pLineDectectTogg->setSelectedIndex(CCUserDefault::sharedUserDefault()->getBoolForKey("s1",true));
			LineDectect = CCMenu::create(pLineDectectTogg,NULL); 

			LineDectect->setPosition(ccp(0,0));
			this->addChild(LineDectect);

			DirectionJudge = setToggleMenu("OFF.png","ON.png",ccp(1581.35,930),((SEL_MenuHandler)&HelloWorld::AngleJudgeCallback),
				CCUserDefault::sharedUserDefault()->getBoolForKey("s2",false));
			DirectionJudge->setPosition(ccp(0,0));
			this->addChild(DirectionJudge);

			//confirm
			AngleJudge = setToggleMenu("OFF.png","ON.png",ccp(1581.35,848),((SEL_MenuHandler)&HelloWorld::DirectionJudgeCallback),
				CCUserDefault::sharedUserDefault()->getBoolForKey("s3",false));
			AngleJudge->setPosition(ccp(0,0));
			this->addChild(AngleJudge);

			  timer = CCLabelTTF::create("Init...", "Arial", 32);
			
			timer->setScaleX(scaleRatio.x);
			timer->setScaleY(scaleRatio.y);
			timer->setPosition(ccp(1504.45*scaleRatio.x,40.8*scaleRatio.y));
			this->addChild(timer);
			


			angler = CCLabelTTF::create("Init...", "Arial", 32);
			angler->setScaleX(scaleRatio.x);
			angler->setScaleY(scaleRatio.y);
			angler->setPosition(ccp(1504.45*scaleRatio.x,116*scaleRatio.y));
			this->addChild(angler);

			
		
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
         pLabel = CCLabelTTF::create("=====Dev Mode=====", "Arial", 36);
		 pLabel->setPositionX(1676.4 * scaleRatio.x);;
		 pLabel->setPositionY(668.2 * scaleRatio.y);
		 pLabel->setScaleX(scaleRatio.x);
		 pLabel->setScaleY(scaleRatio.y);
	//	 pLabel->setAnchorPoint(ccp(1,0));
		 pLabel->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentLeft);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel);
		this->schedule(schedule_selector(HelloWorld::Update));
		
	//	CCLOG("x = %.2f",x); 
        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::LineDectectCallback(CCObject* pSender)
{
	printf("HelloWorld::LineDectectCallback\n");
	customDraw->switches[0] = 1 - customDraw->switches[0];
	CCUserDefault::sharedUserDefault()->setBoolForKey("s1",customDraw->switches[0]);
	CCUserDefault::sharedUserDefault()->flush();
}
void HelloWorld::AngleJudgeCallback(CCObject* pSender)
{
		printf("HelloWorld::AngleJudgeCallback\n");
		
	customDraw->switches[1] = 1 - customDraw->switches[1];
	
	CCUserDefault::sharedUserDefault()->setBoolForKey("s2",customDraw->switches[1]);
	CCUserDefault::sharedUserDefault()->flush();
}
void HelloWorld::DirectionJudgeCallback(CCObject* pSender)
{
		printf("HelloWorld::DirectionJudgeCallback\n");
		CCMessageBox("Working in progress.. =D","Well.. ");
		/*
			customDraw->switches[2] = 1 - customDraw->switches[2];
			
	CCUserDefault::sharedUserDefault()->setBoolForKey("s3",customDraw->switches[2]);
	CCUserDefault::sharedUserDefault()->flush();
	*/
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

cocos2d::CCMenu* HelloWorld::setToggleMenu( const char* on,const char* off,CCPoint pos,cocos2d::SEL_MenuHandler callBack,int setIndex)
{
	CCMenuItemToggle *pLineDectectTogg = CCMenuItemToggle::create(this, callBack ,
		CCMenuItemImage::create(on,
		on),
	
		CCMenuItemImage::create(off,
		off),NULL);

			pLineDectectTogg->setScaleX(scaleRatio.x);
			pLineDectectTogg->setScaleY(scaleRatio.y);
			pLineDectectTogg->setPosition(ccp(pos.x*scaleRatio.x,pos.y*scaleRatio.y));
			pLineDectectTogg->setSelectedIndex(setIndex);
			return CCMenu::create(pLineDectectTogg,NULL);
}

CCPoint	HelloWorld::scaleRatio = ccp(0,0);

void HelloWorld::Update(float dt)
{ 
	customDraw->switches;
	totalTime+=dt;
	char text[10];
	sprintf_s(text,"%.1f",totalTime);
	timer->setString(text);
	pLabel->setString(customDraw->info.c_str());
	if(customDraw->curStatus == CustomDraw::GameStatus::AngelGame)
	{
	
		float s = (customDraw->cicle->getPercentage()*0.01*360);
	sprintf_s(text,"%.1f",s);
	angler->setString(text);
	
	sprintf_s(text,"%.1f",CC_RADIANS_TO_DEGREES( customDraw->angle));
	}

}

void HelloWorld::OKCallback( CCObject* pSender )
{
	printf("OK PRESSED\n");
	if(customDraw->subStatus!=CustomDraw::SubStatus::Submit)
	{
		if(customDraw->curStatus == CustomDraw::GameStatus::LineGame)
		{
		if(ccpDistance(customDraw->Target,ccp(0,0)) == 0)
		{
			CCMessageBox("You might missed something =]","Ehh.. ");
		return;
		}
		}
	 	//pLabel->setVisible(true);
		customDraw->subStatus = CustomDraw::SubStatus::Submit;
	}
	else
	{
		customDraw->curStatus = CustomDraw::GameStatus::Init;
		//pLabel->setVisible(false);
	}

}



