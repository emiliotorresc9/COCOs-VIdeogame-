#ifndef __BANK_SCENE_H__
#define __BANK_SCENE_H__

#include "cocos2d.h"

class BankScene : public cocos2d::Scene
{
public:
    // Funci�n para crear la escena
    static cocos2d::Scene* createScene();

    // Funci�n de inicializaci�n
    virtual bool init();

    // Funci�n para crear los botones de interacci�n
    void crearInteractionButtons();

    // Funciones para mostrar y ocultar las im�genes correspondientes
    void showHideSafe(Ref* sender);
    void showHideCheck(Ref* sender);
    void showHideComputer(Ref* sender);
    void showHideDialog(Ref* sender);

    // Configurar el listener de teclado
    void setupKeyboardListener();

    // Configurar el listener del teclado para cambiar entre escenas
    void setupArrowKeyListener();

    // Variables para almacenar las im�genes
    cocos2d::Sprite* safeImage;
    cocos2d::Sprite* checkImage;
    cocos2d::Sprite* computerImage;
    cocos2d::Sprite* dialogImage;

    // Macro de creaci�n
    CREATE_FUNC(BankScene);
};

#endif // __BANK_SCENE_H__
