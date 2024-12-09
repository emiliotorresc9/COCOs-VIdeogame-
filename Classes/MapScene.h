#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

class MapScene : public cocos2d::Scene
{
public:
    // Función para crear la escena
    static cocos2d::Scene* createScene();

    // Función de inicialización
    virtual bool init();

    // Función para configurar la escena anterior
    static void setPreviousScene(cocos2d::Scene* scene);

    // Macro de creación
    CREATE_FUNC(MapScene);

private:
    static cocos2d::Scene* previousScene;  // Variable estática para almacenar la escena anterior
};

#endif // __MAP_SCENE_H__
