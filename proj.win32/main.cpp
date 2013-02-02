#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

// uncomment below line, open debug console
 #define USE_WIN32_CONSOLE
long millisecondNow()  
{ 
struct cc_timeval now; 
CCTime::gettimeofdayCocos2d(&now, NULL); 
return (now.tv_sec * 1000 + now.tv_usec / 1000); 
} 

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
	
	printf("Console UP!\n");
#endif
	
    // create the application instance
    AppDelegate app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
   eglView.setViewName("NexusEast");
    eglView.setFrameSize(854, 480);
    //eglView.setFrameSize(1280, 720);
	printf("=====================Init Game=====================\n");
	printf("Video Mode = %.2fx%.2f\n",eglView.getFrameSize().width,eglView.getFrameSize().height);
	printf("Clint Window Name:%s\n",eglView.getViewName());
	printf("System Time:%d\n",millisecondNow());
	CCLOG("console?");
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    // eglView.setDesignResolutionSize(480, 320);

    int ret = CCApplication::sharedApplication().run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif
	
	CCUserDefault::sharedUserDefault()->flush(); 
    return ret;
}
