#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

class MapScene : public cocos2d::Scene
{
public:
    // Funci�n para crear la escena
    static cocos2d::Scene* createScene();

    // Funci�n de inicializaci�n
    virtual bool init();

    // Funci�n para configurar la escena anterior
    static void setPreviousScene(cocos2d::Scene* scene);

    // Macro de creaci�n
    CREATE_FUNC(MapScene);

private:
    static cocos2d::Scene* previousScene;  // Variable est�tica para almacenar la escena anterior
};

#endif // __MAP_SCENE_H__
