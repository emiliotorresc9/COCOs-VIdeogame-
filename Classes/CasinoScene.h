#ifndef __CASINO_SCENE_H__
#define __CASINO_SCENE_H__

#include "cocos2d.h"

class CasinoScene : public cocos2d::Scene
{
public:
    // Función para crear la escena
    static cocos2d::Scene* createScene();

    // Función de inicialización
    virtual bool init();

    // Funciones para mostrar u ocultar las imágenes al presionar los botones
    void showHideDialog(cocos2d::Ref* sender);
    void showHideCards(cocos2d::Ref* sender);
    void showHidePaper(cocos2d::Ref* sender);
    void showHideTequila(cocos2d::Ref* sender);

    // Función para crear los botones de interacción
    void crearInteractionButtons();

    // Configurar el listener del teclado para ocultar las imágenes con ESC
    void setupKeyboardListener();

    // Configurar el listener del teclado para cambiar entre escenas con las flechas
    void setupArrowKeyListener();

    // Crear las imágenes de interacción
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* cardsImage;
    cocos2d::Sprite* paperImage;
    cocos2d::Sprite* tequilaImage;

    // Macro de creación
    CREATE_FUNC(CasinoScene);
};

#endif // __CASINO_SCENE_H__
