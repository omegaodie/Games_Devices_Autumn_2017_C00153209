#include "AppDelegate.h"
#include "MainMenu.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

typedef struct tagResource
{
	cocos2d::Size size;
	char directory[100];
} Resource;


// Landscape config.
// 800x480 = Normal screen, WVGA 
static Resource smallResource = { cocos2d::Size(800, 480), "sd" };
// 1280x800 = Extra large screen, WXGA, medium density screen (160)
static Resource mediumResource = { cocos2d::Size(1280, 800), "hd" };
// 1900x1200 = WUXGA, Devices with such as Nexus 7, Nvidia Shield.
static Resource largeResource = { cocos2d::Size(1920, 1200), "shd" };

static cocos2d::Size designResolutionSize = smallResource.size;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("TestGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("TestGame");
#endif
        director->setOpenGLView(glview);
    }


	auto fileUtils = FileUtils::getInstance();

	// Set the design resolution with the NO_BORDER policy.
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	cocos2d::Size frameSize = glview->getFrameSize();
	std::vector<std::string> searchPath;



	// Create the GameData singleton.
	m_ptr = GameData::sharedGameData();
	// Create the level loader object to load general game data.
	LevelLoader loader("GeneralGameData.json");

	// Here, we select the most appropriate resource (i.e. image set) according to the actual frame height of the device.
	// If the resource (image) size is different from design resolution size, we need to set content scale factor.
	// This will either scale the images up or down to match the design resolution size.
	// The content scale factor is the ratio of the resource's height to the height of design resolution.

	// if the frame's height is larger than the height of medium resource size, select large resource.
	float scaleFactor = 1.0f;
	if (frameSize.height > mediumResource.size.height) {
		searchPath.push_back(largeResource.directory);
		scaleFactor = largeResource.size.height / designResolutionSize.height;
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallResource.size.height) {
		searchPath.push_back(mediumResource.directory);
		scaleFactor = mediumResource.size.height / designResolutionSize.height;
	}
	// if the frame's height is smaller than the height of medium resource size, select small resource.
	else {
		searchPath.push_back(smallResource.directory);
		scaleFactor = smallResource.size.height / designResolutionSize.height;
	}

	director->setContentScaleFactor(scaleFactor);
	fileUtils->setSearchPaths(searchPath);

	// Set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// Run
	auto scene = MainMenu::createScene();
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
