#ifndef __CHURCH_SCENE_H__
#define __CHURCH_SCENE_H__

#include "cocos2d.h"

class ChurchScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // Funciones para mostrar y ocultar las imágenes de los objetos en la iglesia
    void showHideScript(Ref* sender);
    void showHideChest(Ref* sender);
    void showHideDialog(Ref* sender);
    void showHideBible(Ref* sender);

    // Función para configurar el listener del teclado (ESC para ocultar imágenes)
    void setupKeyboardListener();

    // Función para configurar el listener de las flechas para cambiar de escena
    void setupArrowKeyListener();

    // Macro de creación
    CREATE_FUNC(ChurchScene);

private:
    // Variables para las imágenes de los objetos en la iglesia
    cocos2d::Sprite* scriptImage;
    cocos2d::Sprite* chestImage;
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* bibleImage;

    // Función para crear los botones de interacción
    void crearInteractionButtons();
};

#endif // __CHURCH_SCENE_H__

