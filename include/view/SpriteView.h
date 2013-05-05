#ifndef SPRITE_VIEW_H
#define SPRITE_VIEW_H

#include "base/View.h"
#include "sol/types.h"

class SpriteView : public View
{
public:
    virtual void refreshSelection (const SpriteSelection &selection) = 0;
    virtual void refreshAnimation (const QString &name) = 0;
    virtual void addAnimation (const QString &name) = 0;
    virtual void removeAnimation (const QString &name) = 0;
    virtual void renameAnimation (
        const QString &oldName, const QString &newName
    ) = 0;
};

#endif
