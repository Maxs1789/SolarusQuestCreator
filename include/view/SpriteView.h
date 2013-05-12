#ifndef SPRITE_VIEW_H
#define SPRITE_VIEW_H

#include "base/View.h"
#include "sol/types.h"

/**
 * @brief Classe abstraite d'une vue de Sprite.
 */
class SpriteView : public View
{
public:
    /**
     * @brief Appelée lorsque la sélection du Sprite change.
     *
     * @param selection La nouvelle sélection du Sprite
     */
    virtual void refreshSelection (const SpriteSelection &selection) = 0;
    /**
     * @brief Appelée lorsqu'une animation a changée.
     *
     * @param name Le nom de l'animation
     */
    virtual void refreshAnimation (const QString &name) = 0;
    /**
     * @brief Appelée lorsqu'une nouvelle animation a été ajoutée au Sprite.
     *
     * @param name Le nom de l'animation
     */
    virtual void addAnimation (const QString &name) = 0;
    /**
     * @brief Appelée lorsqu'une animation a été suprimée du Sprite.
     *
     * @param name Le nom de l'animation
     */
    virtual void removeAnimation (const QString &name) = 0;
    /**
     * @brief Appelée lorsqu'une animation du Sprite à été renommée.
     *
     * @param oldName L'ancien nom de l'animation
     * @param newName Le nouveau nom de l'animation
     */
    virtual void renameAnimation (
        const QString &oldName, const QString &newName
    ) = 0;
};

#endif
