#ifndef __BOAT_SCENE_H__
#define __BOAT_SCENE_H__

#include "cocos2d.h"

class BoatScene : public cocos2d::Scene
{
public:
    // Funci�n para crear la escena
    static cocos2d::Scene* createScene();

    // Funci�n de inicializaci�n
    virtual bool init();

    // Funci�n para crear los botones de interacci�n
    void crearInteractionButtons();

    // Funciones para mostrar y ocultar las im�genes correspondientes
    void showHideDialog(Ref* sender);
    void showHideNews(Ref* sender);
    void showHidePhone(Ref* sender);
    void showHideMap(Ref* sender);

    // Configurar el listener del teclado
    void setupKeyboardListener();

    // Configurar el listener del teclado para cambiar entre escenas
    void setupArrowKeyListener();

    // Variables para almacenar las im�genes
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* newsImage;
    cocos2d::Sprite* phoneImage;
    cocos2d::Sprite* mapImage;

    // Macro de creaci�n
    CREATE_FUNC(BoatScene);
};

#endif // __BOAT_SCENE_H__
