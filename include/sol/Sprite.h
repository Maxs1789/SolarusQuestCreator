/*
 * Solarus Quest Creator - GUI to build games for Solarus engine
 * Copyright (C) 2013, Van den Branden Maxime <max.van.den.branden@gmail.com>
 *
 * Licensed under the EUPL, Version 1.1
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the Licence is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the Licence for the specific language governing permissions and
 * limitations under the Licence.
 */
#ifndef SPRITE_H
#define SPRITE_H

#include <QMap>
#include <lua.hpp>
#include "base/Model.h"
#include "view/SpriteView.h"
#include "exception/IOException.h"
#include "Resource.h"
#include "SpriteSelection.h"
#include "SpriteAnimation.h"

class Sprite : public Resource, public Model<SpriteView>
{
public:
    static const QString p_animation;

    static Sprite *load (QString dataDirectory, QString id, QString name)
        throw(SQCException);

    Sprite (QString id, QString name = "new sprite");

    void save (QString dataDirectory) throw(SQCException);

    Sprite copy () const;

    bool animationExists (QString name) const;
    SpriteAnimation animation (QString name) const throw(SQCException);
    QList<SpriteAnimation> animations (QList<QString> names) const;
    QList<QString> animationNames () const;
    QList<SpriteAnimation> allAnimations () const;

    SpriteSelection selection () const;

    QString filename () const;

    void setName (QString name);

    bool removeAnimation (QString name);
    void setAnimation (QString name, const SpriteAnimation &animation);

    void renameAnimation (QString name, QString newName) throw(SQCException);

    void setSelection (const SpriteSelection &selection) throw(SQCException);

protected:
    void onActionNotify (Action *action, SpriteView *view);
    void onUserNotify (int userType, SpriteView *view);

private:
    QMap<QString, SpriteAnimation> _animations;
    SpriteSelection _selection;

    QString _setName (QString name);
    SpriteAnimation _setAnimation (QString name, SpriteAnimation animation);
    void _addAnimations (
        QList<QString> names, QList<SpriteAnimation> animations
    );
    QList<SpriteAnimation> _removeAnimations (QList<QString> names);
    void _renameAnimation (QString oldName, QString newName);

    void _checkAnimationExists (QString name) const throw(SQCException);
    void _checkAnimationNExists (QString name) const throw(SQCException);
    void _checkSelection (const SpriteSelection &selection) const
        throw(SQCException);
};

#endif
