#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	m_pLayout = NULL;
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    //
    //// position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(pLabel, 1);

    //// add "HelloWorld" splash screen"
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(pSprite, 0);

	Layout *pLayout = dynamic_cast<UILayout *>(GUIReader::shareReader()->widgetFromJsonFile("level_select.json"));
	if(pLayout)
	{
		pLayout->setPosition(ccp(-200,0));
		this->addChild(pLayout);

		ActionObject* act = NULL;
		act = ActionManager::shareManager()->getActionByName("level_select.json","texiao");
		if(NULL != act)
			act->play();
		act = ActionManager::shareManager()->getActionByName("level_select.json","shuibodonghua");
		if(NULL != act)
			act->play();
	}
    
    return true;
}

int g_layoutcnt = 0;
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif

	int t = g_layoutcnt%2;
	if( t == 0)
	{
		m_pLayout = dynamic_cast<UILayout *>(GUIReader::shareReader()->widgetFromJsonFile("level_select_1.json"));
		if(m_pLayout)
		{
			m_pLayout->setPosition(ccp(-200,0));
			this->addChild(m_pLayout);

			ActionObject* act = NULL;
			act = ActionManager::shareManager()->getActionByName("level_select_1.json","texiao");
			if(NULL != act)
				act->play();
			act = ActionManager::shareManager()->getActionByName("level_select_1.json","shuibodonghua");
			if(NULL != act)
				act->play();
		}
	}
	else
	{
		//ActionManager::shareManager()->stopAllActionByJson("level_select_1.json");
		//ActionManager::shareManager()->stopAllActionByJson("level_select.json");

		ActionObject* act = NULL;
		act = ActionManager::shareManager()->getActionByName("level_select_1.json","texiao");
		if(NULL != act)
			act->stop();
		act = ActionManager::shareManager()->getActionByName("level_select_1.json","shuibodonghua");
		if(NULL != act)
			act->stop();

		ActionManager::shareManager()->releaseActions();

		if(m_pLayout)
		{
			m_pLayout->removeFromParent();
			m_pLayout = NULL;
		}

		//CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	}

	g_layoutcnt++;
}
