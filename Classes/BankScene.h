#ifndef __BANK_SCENE_H__
#define __BANK_SCENE_H__

#include "cocos2d.h"

class BankScene : public cocos2d::Scene
{
public:
    // Función para crear la escena
    static cocos2d::Scene* createScene();

    // Función de inicialización
    virtual bool init();

    // Función para crear los botones de interacción
    void crearInteractionButtons();

    // Funciones para mostrar y ocultar las imágenes correspondientes
    void showHideSafe(Ref* sender);
    void showHideCheck(Ref* sender);
    void showHideComputer(Ref* sender);
    void showHideDialog(Ref* sender);

    // Configurar el listener de teclado
    void setupKeyboardListener();

    // Configurar el listener del teclado para cambiar entre escenas
    void setupArrowKeyListener();

    // Variables para almacenar las imágenes
    cocos2d::Sprite* safeImage;
    cocos2d::Sprite* checkImage;
    cocos2d::Sprite* computerImage;
    cocos2d::Sprite* dialogImage;

    // Macro de creación
    CREATE_FUNC(BankScene);
};

#endif // __BANK_SCENE_H__
