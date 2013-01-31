#include "CustomDraw.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
CustomDraw::CustomDraw(void)
{
	angle=0;
	targetAngle=  0;
	CCLayer::create();
	isTouched = false;
	switches[0] = CCUserDefault::sharedUserDefault()->getBoolForKey("s1",true);
	switches[1] = CCUserDefault::sharedUserDefault()->getBoolForKey("s2",false);
	switches[2] = CCUserDefault::sharedUserDefault()->getBoolForKey("s3",false);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	curStatus = GameStatus::Init;
	subStatus = Generate;
	srand(time(NULL));
	this->setScaleX(HelloWorld::scaleRatio.x);
	this->setScaleY(HelloWorld::scaleRatio.y);
}


CustomDraw::~CustomDraw(void)
{
}

void CustomDraw::DrawLine( cocos2d::CCPoint start,cocos2d::CCPoint end ,float width)
{
	for(int i = 0;i<5;i++)
	{

		GLfloat shadow = i*.1f-0.5;	
		ccDrawColor4F(1-shadow,1-shadow,1-shadow,0.1);
		glLineWidth(i*width/2);
		ccDrawLine(start,end);
		CHECK_GL_ERROR_DEBUG();

	}
	ccDrawColor4F(1,1,0.3,1);
	glLineWidth( width);
	ccDrawLine(start,end);
	CHECK_GL_ERROR_DEBUG();

}

void CustomDraw::ClearLayer()
{

}

void CustomDraw::draw()
{
	CCLayer::draw();
	CustomUpdate();
} 
 
void CustomDraw::CustomUpdate()
{
	switch (curStatus)
	{
	case Init:
		curStatus = GetGameRandom;
		subStatus = Generate;
		Target = ccp(0,0);
		break;
	case  GetGameRandom:
		{
			int i = rand()%3; 
			printf("random: %d\n",i);
			if(switches[i])
				curStatus =(GameStatus)(i+2);
		}

		break;

#pragma region LineGame
	case  LineGame: 
		{

			/*

			(407.15,755.15)----(1029.25,755.15)
			|		|
			|		|
			(407.15,133.05)----(1029.25,133.05)
			we well get some random points inside this box to generate lines

			*/
			
				 
			switch (subStatus)
			{
			case CustomDraw::Generate:
				{
					printf("Generating line...\n");
					start = ccp(rand()%1029+407,rand()%755+133);
					end = ccp(rand()%1029+407,rand()%755+133);

					while(ccpDistance(start,end)<50)
					{
						start = ccp(rand()%1029+407,rand()%755+133);
						end = ccp(rand()%1029+407,rand()%755+133);
						printf("Failed Generating Line. Retrying...\n");
					}
				}
				printf("Done.\n");
				printf("Generated Point:\n\t start.x = %.2f,start.y = %.2f\n\t end.x = %.2f,end.y = %.2f \n",
					start.x,start.y,end.x,end.y);
				subStatus = Play;
				break;
			case CustomDraw::Play:
				{
					DrawLine(start,	end,5);
					CCPoint point = ccp(touchPos.x/HelloWorld::scaleRatio.x,touchPos.y/HelloWorld::scaleRatio.y);
					CCPoint tgt = point2line(start,	end,point);
					if(isTouched)
					{
					Target = tgt;
						glPointSize(9);
						ccDrawPoint(point);
						ccDrawPoint(tgt);
						DrawLine(point,	tgt,2);
					}
				}
				break;

			case CustomDraw::Submit:
				{
				DrawLine(start,	end,5);
				ccDrawColor4B(255,0,0,255);
				ccDrawPoint(Target);

				
				ccDrawColor4B(0,255,0,255);
				ccDrawPoint(ccpMidpoint(start,end));
				float res = ccpDistance(Target,ccpMidpoint(start,end));
				printf("distance:%.2f\n",res);
				addPower = (20 - (int)res);
				}
				break;
			default:
				break;
			}




			 

		}

		break;

#pragma endregion


	case  AngelGame:


		{
			CCPoint midScreen = ccp(CCDirector::sharedDirector()->getWinSizeInPixels().height/2,
				CCDirector::sharedDirector()->getWinSizeInPixels().width/2);
			switch (subStatus)
			{
			case CustomDraw::Generate:
				{

					printf("Generating Angle...\n");
					 angle = rand()%360;
					 
					printf("Generated:%.2f\n",angle);
					angle = CC_DEGREES_TO_RADIANS(angle);
					printf("Generated:%.2f\n",angle);
				
				}
				printf("Done.\n");
				subStatus = Play;
				break;
			case CustomDraw::Play:
				{
					CCPoint angg = ccpForAngle(angle); 
					CCPoint offset = ccp(800,500);
					angg = ccpMult(angg,200);
					angg = ccpAdd(angg,offset);
					//printf("ang = %.2f,ang.x =% .2f,ang.y = %.2f\n",angle,angg.x,angg.y);
					DrawLine(offset,angg,1);
					DrawLine(offset,ccp(offset.x+200,offset.y),1);
			}
				break;
			case CustomDraw::Submit:
				{
				addPower = 20 - abs(CC_RADIANS_TO_DEGREES(angle) - targetAngle*0.01*360);
				printf("score:%.2f\n",addPower);
					CCPoint angg = ccpForAngle(angle); 
					CCPoint offset = ccp(800,500);
					angg = ccpMult(angg,200);
					angg = ccpAdd(angg,offset);
					//printf("ang = %.2f,ang.x =% .2f,ang.y = %.2f\n",angle,angg.x,angg.y);
					DrawLine(offset,angg,1);
					DrawLine(offset,ccp(offset.x+200,offset.y),1);
			}
				break;
			default:
				break;
			}
		}
		//printf("AngelGame\n");
		break;
	case  DirectionGame:

		printf("DirectionGame\n");
		break;
	default:
		break;
	}

}

float  CustomDraw::ccp2Angle(cocos2d::CCPoint from,cocos2d::CCPoint to)
{
	float o = to.x - from.x;
	float a = to.y - from.y;
	return  (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
}

cocos2d::CCPoint CustomDraw::point2line( cocos2d::CCPoint start,cocos2d::CCPoint end,cocos2d::CCPoint point )
{

	float  r=relation(start,end,point);
	CCPoint tp; 
	tp.x=start.x+r*(end.x-start.x); 
	tp.y=start.y+r*(end.y-start.y); 
	return tp; 

	//return res;
}
bool	CustomDraw::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	cocos2d::CCPoint touchPoint = touch->locationInView();
	touchPoint = cocos2d::CCDirector::sharedDirector()->convertToGL(touchPoint);
	touchPos = touchPoint;
	touchPosBegin = touchPoint;
	isTouched = true;
	return true;
}

double CustomDraw::dotmultiply( cocos2d::CCPoint p1,cocos2d::CCPoint p2,cocos2d::CCPoint p0 )
{

	return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y)); 

}

double CustomDraw::relation( cocos2d::CCPoint start,cocos2d::CCPoint end,cocos2d::CCPoint p )
{


	CCPoint s,e; 
	s=start; 
	e=p; 
	return dotmultiply(e,end,start)/(ccpDistance(start,end)*ccpDistance(start,end)); 
}

void CustomDraw::ccTouchMoved( cocos2d::CCTouch* touch, cocos2d::CCEvent* event )
{
	cocos2d::CCPoint touchPoint = touch->locationInView();
	touchPoint = cocos2d::CCDirector::sharedDirector()->convertToGL(touchPoint);
	targetAngle = ccpDistance(touchPosBegin,touchPoint)/2;
	 if(targetAngle>100)targetAngle=100;
	printf("targetAngle:%.2f\n",targetAngle);
	// touchPos = touchPoint;
}

void CustomDraw::ccTouchEnded( cocos2d::CCTouch* touch, cocos2d::CCEvent* event )
{
	cocos2d::CCPoint touchPoint = touch->locationInView();
	touchPoint = cocos2d::CCDirector::sharedDirector()->convertToGL(touchPoint);
	touchPos = touchPoint;
	isTouched = false;
}

cocos2d::CCPoint CustomDraw::scaleDown( cocos2d::CCPoint point )
{
	return ccp(point.x * HelloWorld::scaleRatio.x , point.y * HelloWorld::scaleRatio.y);
}

float CustomDraw::Lookat(CCPoint from,CCPoint to)
{
	float o = to.x - from.x;
		float a = to.y - from.y;
		float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

		if( a < 0 ) 
			{
			if(  o < 0 )
				at = 180 + fabs(at);
			else
				at = 180 - fabs(at);    
			}
		return at;
}