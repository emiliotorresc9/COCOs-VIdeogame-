#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // Función de callback para manejar el botón "Play"
    void playButtonCallback(cocos2d::Ref* pSender);

    // Macro de creación
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
