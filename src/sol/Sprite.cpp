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
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include "sol/Sprite.h"
#include "base/Setter.h"
#include "base/Adder.h"
#include "base/Remover.h"
#include "base/SubModelSetter.h"
#include "base/SubModelRename.h"
#include "util/FileTools.h"

#define NOTIFY_SELECTION 1
#define A_SET_ANIMATION 12
#define A_ADD_ANIMATION 13
#define A_REMOVE_ANIMATION 14

const QString Sprite::p_animation = "animation";

Sprite::Sprite (QString id, QString name) :
    Resource(SPRITE, id, name)
{}

Sprite Sprite::copy () const
{
    Sprite sprite(id(), _name);
    sprite._animations = _animations;
    return sprite;
}

Sprite *Sprite::load (QString dataDirectory, QString id, QString name)
    throw(SQCException)
{
    QString filename = dataDirectory + "sprites/" + id + ".dat";
    if (!FileTools::fileExists(filename)) {
        throw new IOException(IOException::FILE_N_EXISTS, filename);
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw new IOException(IOException::FILE_N_READ, filename);
    }
    Sprite *sprite = new Sprite(id, name);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line != "") {
            QStringList list = line.split(" ");
            if (list.length() == 5) {
                QString name = list[0];
                int frameDelay = list[3].toInt();
                int frameOnLoop = list[4].toInt();
                SpriteAnimation animation(
                    name, list[1], frameDelay, frameOnLoop
                );
                int nDirections = list[2].toInt();
                int i = 0;
                while (!in.atEnd() && i < nDirections) {
                    line = in.readLine();
                    list = line.split("\t");
                    if (list.size() == 8) {
                        int x = list[0].toInt();
                        int y = list[1].toInt();
                        int w = list[2].toInt();
                        int h = list[3].toInt();
                        int oX = list[4].toInt();
                        int oY = list[5].toInt();
                        int nF = list[6].toInt();
                        int nC = list[7].toInt();
                        SpriteDirection direction(x, y, w, h, oX, oY, nF, nC);
                        animation.addDirection(direction);
                        i++;
                    }
                }
                sprite->_animations[name] = animation;
            }
        }
    }
    file.close();
    return sprite;
}

bool Sprite::isSaved () const
{
    return checkSaveReference();
}

void Sprite::save (QString dataDirectory) throw(SQCException)
{
    if (checkSaveReference()) {
        return;
    }
    QString filename = dataDirectory + "sprites/" + id() + ".dat";
    QFileInfo info(filename);
    QString dir = info.absoluteDir().absolutePath();
    QFile file(filename);
    if (!FileTools::directoryExists(dir)) {
        FileTools::makeDirectory(dir);
    }
    if (!file.open(QIODevice::WriteOnly)) {
        throw new IOException(IOException::FILE_N_WRITE, filename);
    }
    QList<QString> names = _animations.keys();
    for (int i = 0; i < names.size(); i++) {
        QString str = _animations[names[i]].toData();
        file.write(str.toLocal8Bit());
        file.write("\n\n");
    }
    file.close();
    resetSaveReference();
}

bool Sprite::animationExists (QString name) const
{
    return _animations.contains(name);
}

SpriteAnimation Sprite::animation (QString name) const throw(SQCException)
{
    _checkAnimationExists(name);
    return _animations[name];
}

QList<SpriteAnimation> Sprite::animations (QList<QString> names) const
{
    QList<SpriteAnimation> list;
    for (int i = 0; i < names.size(); i++) {
        if (_animations.contains(names[i])) {
            list.push_back(_animations[names[i]]);
        }
    }
    return list;
}

QList<QString> Sprite::animationNames () const
{
    return _animations.keys();
}

QList<SpriteAnimation> Sprite::allAnimations () const
{
    return _animations.values();
}

SpriteSelection Sprite::selection () const
{
    return _selection;
}

QString Sprite::filename () const
{
    return QString("sprites/") + id() + ".dat";
}

void Sprite::setName (QString name)
{
    if (name != _name) {
        doAction(new Setter<Sprite, QString>(
            this, Resource::p_name, &Sprite::_setName, name
        ));
    }
}

bool Sprite::removeAnimation (QString name)
{
    if (_animations.contains(name)) {
        QList<QString> names;
        names.push_back(name);
        doAction(new Remover<Sprite, SpriteAnimation, QString>(
            this, Sprite::p_animation, &Sprite::_removeAnimations,
            &Sprite::_addAnimations, names, A_REMOVE_ANIMATION
        ));
        return true;
    }
    return false;
}

void Sprite::setAnimation (QString name, const SpriteAnimation &animation)
{
    if (_animations.contains(name)) {
        doAction(new SubModelSetter<Sprite, SpriteAnimation, QString>(
            this, Sprite::p_animation, &Sprite::_setAnimation,
            name, SpriteAnimation(animation, name), A_SET_ANIMATION
        ));
    } else {
        QList<QString> ids;
        QList<SpriteAnimation> animations;
        ids.push_back(name);
        animations.push_back(SpriteAnimation(animation, name));
        doAction(new Adder<Sprite, SpriteAnimation, QString>(
            this, Sprite::p_animation, &Sprite::_addAnimations,
            &Sprite::_removeAnimations, ids, animations, A_ADD_ANIMATION
        ));
    }
}

void Sprite::renameAnimation (QString name, QString newName) throw(SQCException)
{
    if (newName == "") {
        throw SQCException(QObject::tr("animation name cannot be empty"));
    }
    if (name != newName) {
        _checkAnimationExists(name);
        _checkAnimationNExists(newName);
        doAction(new SubModelRename<Sprite, QString>(
            this, Sprite::p_animation, &Sprite::_renameAnimation, name, newName
        ));
    }
}

void Sprite::setSelection (const SpriteSelection &selection) throw(SQCException)
{
    _checkSelection(selection);
    _selection = selection;
    userNotify(NOTIFY_SELECTION);
}

void Sprite::onActionNotify (Action *action, SpriteView *view)
{
    int type = action->type();
    if (type == A_SET_ANIMATION) {
        QString name = (
            (SubModelSetter<Sprite, SpriteAnimation, QString>*)action
        )->id();
        if (_selection.animation() == name) {
            view->refreshAnimation(name);
        } else {
            _selection = SpriteSelection(name);
            view->refreshSelection(_selection);
        }
    } else if (type == A_ADD_ANIMATION || type == A_REMOVE_ANIMATION) {
        QString name = ((GroupAction<QString>*)action)->selection().first();
        if (_animations.contains(name)) {
            view->addAnimation(name);
        } else {
            view->removeAnimation(name);
        }
    } else if (type == RENAME_ACTION) {
        SubModelRename<Sprite, QString>* rAction =
            (SubModelRename<Sprite, QString>*)action;
        view->renameAnimation(rAction->oldId(), rAction->newId());
    }
}

void Sprite::onUserNotify (int userType, SpriteView *view)
{
    if (userType == NOTIFY_SELECTION) {
        view->refreshSelection(_selection);
    }
}

QString Sprite::_setName (QString name)
{
    QString old = _name;
    _name = name;
    return old;
}

SpriteAnimation Sprite::_setAnimation (QString name, SpriteAnimation animation)
{
    SpriteAnimation old = _animations[name];
    _animations[name] = animation;
    if (
        _selection.animation() == name &&
        _selection.direction() >= animation.countDirections()
    ) {
        _selection = SpriteSelection(name);
    }
    return old;
}

void Sprite::_addAnimations (
    QList<QString> names, QList<SpriteAnimation> animations
) {
    QString name = names.first();
    _animations[name] = animations.first();
    _selection = SpriteSelection(name);
}

QList<SpriteAnimation> Sprite::_removeAnimations (QList<QString> names)
{
    QList<SpriteAnimation> animations;
    QString name = names.first();
    animations.push_back(_animations[name]);
    _animations.remove(name);
    if (_selection.animation() == name) {
        _selection = SpriteSelection();
    }
    return animations;
}

void Sprite::_renameAnimation (QString oldName, QString newName)
{
    _animations[newName] = SpriteAnimation(_animations[oldName], newName);
    _animations.remove(oldName);
}

void Sprite::_checkAnimationExists (QString name) const throw(SQCException)
{
    if (!_animations.contains(name)) {
        QString message = QObject::tr("animation '$1' does not exists");
        message.replace("$1", name);
        throw SQCException(message);
    }
}

void Sprite::_checkAnimationNExists (QString name) const throw(SQCException)
{
    if (_animations.contains(name)) {
        QString message = QObject::tr("animation '$1' already exists");
        message.replace("$1", name);
        throw SQCException(message);
    }
}

void Sprite::_checkSelection (const SpriteSelection &selection) const
    throw(SQCException)
{
    if (!selection.isEmpty()) {
        _checkAnimationExists(selection.animation());
        if (selection.haveDirection()) {
            int count = _animations[selection.animation()].countDirections();
            int direction = selection.direction();
            if (direction >= count || direction < 0) {
                QString msg = QObject::tr(
                    "direction $1 does not exists in animation '$2'"
                );
                msg.replace("$1", QString::number(direction));
                msg.replace("$2", selection.animation());
                throw SQCException(msg);
            }
        }
    }
}
