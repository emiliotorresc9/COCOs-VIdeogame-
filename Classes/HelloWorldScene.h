#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // Funci�n de callback para manejar el bot�n "Play"
    void playButtonCallback(cocos2d::Ref* pSender);

    // Macro de creaci�n
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
