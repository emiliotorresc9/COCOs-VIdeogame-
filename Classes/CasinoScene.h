#ifndef __CASINO_SCENE_H__
#define __CASINO_SCENE_H__

#include "cocos2d.h"

class CasinoScene : public cocos2d::Scene
{
public:
    // Funci�n para crear la escena
    static cocos2d::Scene* createScene();

    // Funci�n de inicializaci�n
    virtual bool init();

    // Funciones para mostrar u ocultar las im�genes al presionar los botones
    void showHideDialog(cocos2d::Ref* sender);
    void showHideCards(cocos2d::Ref* sender);
    void showHidePaper(cocos2d::Ref* sender);
    void showHideTequila(cocos2d::Ref* sender);

    // Funci�n para crear los botones de interacci�n
    void crearInteractionButtons();

    // Configurar el listener del teclado para ocultar las im�genes con ESC
    void setupKeyboardListener();

    // Configurar el listener del teclado para cambiar entre escenas con las flechas
    void setupArrowKeyListener();

    // Crear las im�genes de interacci�n
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* cardsImage;
    cocos2d::Sprite* paperImage;
    cocos2d::Sprite* tequilaImage;

    // Macro de creaci�n
    CREATE_FUNC(CasinoScene);
};

#endif // __CASINO_SCENE_H__
