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
#include <QObject>
#include "sol/SpriteAnimation.h"

SpriteAnimation::SpriteAnimation (
    QString name, QString image, int frameDelay, int frameOnLoop
) throw(SQCException) :
    _name(name),
    _image(image),
    _frameDelay(frameDelay),
    _frameOnLoop(frameOnLoop)
{
    _checkName(name);
    _checkFrameDelay(frameDelay);
    _checkFrameOnLoop(frameOnLoop);
}

SpriteAnimation::SpriteAnimation (const SpriteAnimation &other, QString name) :
    _name(name),
    _image(other._image),
    _frameDelay(other._frameDelay),
    _frameOnLoop(other._frameOnLoop),
    _directions(other._directions)
{}

QString SpriteAnimation::name () const
{
    return _name;
}

QString SpriteAnimation::image () const
{
    return _image;
}

int SpriteAnimation::frameDelay () const
{
    return _frameDelay;
}

int SpriteAnimation::frameOnLoop () const
{
    return _frameOnLoop;
}

int SpriteAnimation::countDirections () const
{
    return _directions.size();
}

SpriteDirection SpriteAnimation::direction (const int &n) const
    throw(SQCException)
{
    _checkDirectionExists(n);
    return _directions[n];
}

QList<SpriteDirection> SpriteAnimation::allDirections () const
{
    return _directions;
}

int SpriteAnimation::maxNbFrames () const
{
    int max = 1;
    for (int i = 0; i < _directions.size(); i++) {
        if (_directions[i].nbFrames() > max) {
            max = _directions[i].nbFrames();
        }
    }
    return max;
}

void SpriteAnimation::setImage (const QString &image)
{
    _image = image;
}

void SpriteAnimation::setFrameDelay (const int &frameDelay) throw(SQCException)
{
    _checkFrameDelay(frameDelay);
    _frameDelay = frameDelay;
    if (_frameDelay == 0) {
        _frameOnLoop = -1;
    }
}

void SpriteAnimation::setFrameOnLoop (const int &frameOnLoop)
    throw(SQCException)
{
    _checkFrameOnLoop(frameOnLoop);
    _frameOnLoop = frameOnLoop;
}

int SpriteAnimation::addDirection (const SpriteDirection &direction)
{
    _directions.push_back(direction);
    return _directions.size() - 1;
}

void SpriteAnimation::setDirection (
    const int &n, const SpriteDirection &direction
) {
    if (n < 0 || n >= _directions.size()) {
        _directions.push_back(direction);
    } else {
        _directions[n] = direction;
    }
}

void SpriteAnimation::removeDirection (const int &n) throw(SQCException)
{
    _checkDirectionExists(n);
    _directions.removeAt(n);
}

void SpriteAnimation::swapDirection (const int &n1, const int &n2)
    throw(SQCException)
{
    _checkDirectionExists(n1);
    _checkDirectionExists(n2);
    SpriteDirection t = _directions[n1];
    _directions[n1] = _directions[n2];
    _directions[n2] = t;
}

QString SpriteAnimation::toData () const
{
    QString data = _name + " " + _image + " ";
    data += QString::number(_directions.count()) + " ";
    data += QString::number(_frameDelay) + " ";
    data += QString::number(_frameOnLoop);
    for (int i = 0; i < _directions.count(); i++) {
        data += "\n";
        data += QString::number(_directions[i].x()) + "\t";
        data += QString::number(_directions[i].y()) + "\t";
        data += QString::number(_directions[i].width()) + "\t";
        data += QString::number(_directions[i].height()) + "\t";
        data += QString::number(_directions[i].originX()) + "\t";
        data += QString::number(_directions[i].originY()) + "\t";
        data += QString::number(_directions[i].nbFrames()) + "\t";
        data += QString::number(_directions[i].nbColumns());
    }
    return data;
}

void SpriteAnimation::_checkName (QString name) const throw(SQCException)
{
    if (name == "") {
        throw SQCException(QObject::tr("animation name cannot be empty"));
    }
}

void SpriteAnimation::_checkDirectionExists (int n) const
    throw(SQCException)
{
    if (!_directions.size() > n) {
        QString message = QObject::tr("direction $1 does not exists");
        message.replace("$1", QString::number(n));
        throw SQCException(message);
    }
}

void SpriteAnimation::_checkFrameDelay (int frameDelay) const
    throw(SQCException)
{
    if (frameDelay < 0) {
        throw SQCException(
            QObject::tr("frame delay must be greater or equals than 0")
        );
    }
}

void SpriteAnimation::_checkFrameOnLoop (int frameOnLoop) const
    throw(SQCException)
{
    if (_frameDelay == 0 && frameOnLoop != -1) {
        throw SQCException(QObject::tr(
            "frame on loop must be equals than -1 when frame delay equals 0"
        ));
    }
    if (frameOnLoop < -1) {
        throw SQCException(
            QObject::tr("frame on loop must be greater or equals than -1")
        );
    }
}
