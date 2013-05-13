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
#ifndef SPRITE_DIRECTION_PREVIEW_H
#define SPRITE_DIRECTION_PREVIEW_H

#include <QWidget>
#include <QTimer>
#include "sol/SpriteDirection.h"

class QPushButton;
class QLabel;
class SpriteDirectionGraphicsView;
class ColorButton;

class SpriteDirectionPreview : public QWidget
{
    Q_OBJECT
public:
    SpriteDirectionPreview ();

    void setImage (const QPixmap &pix);
    void setDirection (const SpriteDirection &direction);
    void setFrameDelay (const int &frameDelay);
    void setFrameOnLoop (const int &frameOnLoop);

    SpriteDirectionGraphicsView *graphicsView ();

protected:
    void changeEvent (QEvent *event);

private:
    QPixmap _pix;
    SpriteDirection _direction;
    SpriteDirectionGraphicsView *_graphicsView;
    QLabel *_frame;
    QPushButton *_play;
    QPushButton *_next;
    QPushButton *_prev;
    QPushButton *_stop;
    QPushButton *_first;
    QPushButton *_last;
    int _currentFrame;
    bool _inPlaying;
    int _frameDelay;
    int _frameOnLoop;
    QTimer _timer;
    QAction *_actionOriginPoint;
    QAction *_actionOriginCross;

    void _initWidgets ();
    void _connects ();

    void _refreshView ();

private slots:
    void _playAction ();
    void _stopAction ();
    void _nextAction ();
    void _prevAction ();
    void _lastAction ();
    void _firstAction ();

    void _step ();

    void _refreshShowOrigin (bool show, bool cross);

    void _originPointChange (bool point);
    void _originCrossChange (bool cross);
};

#endif
