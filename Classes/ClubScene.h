#ifndef __CLUB_SCENE_H__
#define __CLUB_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ClubScene : public Scene
{
public:
    // Crear la escena
    static Scene* createScene();

    // Inicializar la escena
    virtual bool init();

    // Funciones para crear los botones
    void crearInteractionButtons();

    // Funciones para mostrar y ocultar las imágenes
    void showHideDialog(Ref* sender);
    void showHideBook(Ref* sender);
    void showHideBag(Ref* sender);
    void showHideContract(Ref* sender);

    // Listener para las teclas
    void setupKeyboardListener();
    void setupArrowKeyListener();

    // Crear las variables para las imágenes
    Sprite* dialogImage;
    Sprite* bookImage;
    Sprite* bagImage;
    Sprite* contractImage;

    // Implementar el método 'create' de cocos2d
    CREATE_FUNC(ClubScene);
};

#endif // __CLUB_SCENE_H__
