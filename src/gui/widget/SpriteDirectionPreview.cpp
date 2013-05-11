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
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsPixmapItem>
#include <QEvent>
#include <QToolBar>
#include <QAction>
#include "gui/widget/SpriteDirectionPreview.h"
#include "gui/widget/SpriteDirectionGraphicsView.h"
#include "gui/widget/ColorButton.h"

SpriteDirectionPreview::SpriteDirectionPreview () :
    _currentFrame(0),
    _inPlaying(false),
    _frameDelay(0),
    _frameOnLoop(-1)
{
    _initWidgets();
    _connects();
}

void SpriteDirectionPreview::setImage (const QPixmap &pix)
{
    _pix = pix;
    _refreshView();
}

void SpriteDirectionPreview::setDirection (const SpriteDirection &direction)
{
    _direction = direction;
    _currentFrame = 0;
    _refreshView();
}

void SpriteDirectionPreview::setFrameDelay (const int &frameDelay)
{
    _frameDelay = frameDelay;
    _timer.setInterval(frameDelay);
}

void SpriteDirectionPreview::setFrameOnLoop (const int &frameOnLoop)
{
    _frameOnLoop = frameOnLoop;
}

void SpriteDirectionPreview::changeEvent (QEvent *event)
{
    if (event->type() == QEvent::EnabledChange && isEnabled() == false) {
        _timer.stop();
        _inPlaying = false;
        _currentFrame = 0;
        _graphicsView->scene()->clear();
    }
}

void SpriteDirectionPreview::_initWidgets ()
{
    _graphicsView = new SpriteDirectionGraphicsView;
    _frame = new QLabel;
    _play = new QPushButton(QIcon(":media/play"), "");
    _next = new QPushButton(QIcon(":media/next"), "");
    _prev = new QPushButton(QIcon(":media/prev"), "");
    _stop = new QPushButton(QIcon(":media/stop"), "");
    _first = new QPushButton(QIcon(":media/first"), "");
    _last = new QPushButton(QIcon(":media/last"), "");
    _backColor = new ColorButton(Qt::lightGray);
    _selColor = new ColorButton(_graphicsView->selectionColor());

    _frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _frame->setLineWidth(1);
    _frame->setAlignment(Qt::AlignCenter);
    _frame->setMargin(3);
    _graphicsView->setScene(new QGraphicsScene());
    _graphicsView->setBackgroundBrush(Qt::lightGray);
    _play->setMaximumSize(24, 24);
    _next->setToolTip(tr("Next frame"));
    _next->setMaximumSize(24, 24);
    _prev->setToolTip(tr("Previous frame"));
    _prev->setMaximumSize(24, 24);
    _stop->setToolTip(tr("Stop"));
    _stop->setMaximumSize(24, 24);
    _first->setToolTip(tr("First frame"));
    _first->setMaximumSize(24, 24);
    _last->setToolTip(tr("Last frame"));
    _last->setMaximumSize(24, 24);
    _backColor->setToolTip(tr("Background color"));
    _selColor->setToolTip(tr("Selection color"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(_play);
    buttonLayout->addWidget(_first);
    buttonLayout->addWidget(_prev);
    buttonLayout->addWidget(_frame);
    buttonLayout->addWidget(_next);
    buttonLayout->addWidget(_last);
    buttonLayout->addWidget(_stop);

    QToolBar *toolBar = new QToolBar;
    _actionOriginPoint = toolBar->addAction(
        QIcon(":/graphics/origin_point"), ""
    );
    _actionOriginCross = toolBar->addAction(
        QIcon(":/graphics/origin_cross"), ""
    );
    toolBar->addSeparator();
    toolBar->addWidget(_selColor);
    toolBar->addSeparator();
    toolBar->addWidget(_backColor);
    _actionOriginPoint->setToolTip(tr("Origin point"));
    _actionOriginPoint->setCheckable(true);
    _actionOriginPoint->setChecked(_graphicsView->point());
    _actionOriginCross->setToolTip(tr("Origin cross"));
    _actionOriginCross->setCheckable(true);
    _actionOriginCross->setChecked(_graphicsView->cross());
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setMovable(false);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_graphicsView);
    layout->addLayout(buttonLayout);
    layout->setAlignment(buttonLayout, Qt::AlignCenter);

    QHBoxLayout *toolLayout = new QHBoxLayout;
    toolLayout->addWidget(toolBar);
    toolLayout->addLayout(layout);
    setLayout(toolLayout);
}

void SpriteDirectionPreview::_connects ()
{
    connect(_play, SIGNAL(clicked()), this, SLOT(_playAction()));
    connect(_next, SIGNAL(clicked()), this, SLOT(_nextAction()));
    connect(_prev, SIGNAL(clicked()), this, SLOT(_prevAction()));
    connect(_stop, SIGNAL(clicked()), this, SLOT(_stopAction()));
    connect(_last, SIGNAL(clicked()), this, SLOT(_lastAction()));
    connect(_first, SIGNAL(clicked()), this, SLOT(_firstAction()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(_step()));
    connect(
        _actionOriginPoint, SIGNAL(toggled(bool)),
        this, SLOT(_originPointChange(bool))
    );
    connect(
        _actionOriginCross, SIGNAL(toggled(bool)),
        this, SLOT(_originCrossChange(bool))
    );
    connect(
        _selColor, SIGNAL(colorChange(QColor)),
        _graphicsView, SLOT(setSelectionColor(QColor))
    );
    connect(
        _backColor, SIGNAL(colorChange(QColor)),
        this, SLOT(_backColorChange(QColor))
    );
}

void SpriteDirectionPreview::_refreshView ()
{
    int nbFrames = _direction.nbFrames();
    _frame->setText(
        QString::number(_currentFrame) + "/" + QString::number(nbFrames - 1)
    );
    if (_inPlaying) {
        _play->setIcon(QIcon(":media/pause"));
        _play->setToolTip(tr("Pause"));
    } else {
        _play->setIcon(QIcon(":media/play"));
        _play->setToolTip(tr("Play"));
    }
    _play->setEnabled(nbFrames > 1 && _frameDelay > 0);
    _stop->setEnabled(_inPlaying);
    _prev->setEnabled(!_inPlaying && _currentFrame > 0);
    _first->setEnabled(!_inPlaying && _currentFrame > 0);
    _next->setEnabled(!_inPlaying && _currentFrame < nbFrames - 1);
    _last->setEnabled(!_inPlaying && _currentFrame < nbFrames - 1);
    int x = _direction.x(), y = _direction.y();
    int w = _direction.width(), h = _direction.height();
    int col = _currentFrame % _direction.nbColumns();
    int row = _currentFrame / _direction.nbColumns();
    _graphicsView->scene()->clear();
    x += col * w;
    y += row * h;
    QPixmap pix = _pix.copy(x, y, w, h);
    _graphicsView->scene()->addItem(new QGraphicsPixmapItem(pix));
    _graphicsView->scene()->setSceneRect(pix.rect());
    _graphicsView->setOrigin(_direction.originX(), _direction.originY());
}

void SpriteDirectionPreview::_playAction ()
{
    if (_inPlaying) {
        _timer.stop();
        _inPlaying = false;
    } else if (_frameDelay > 0) {
        _timer.start();
        _inPlaying = true;
    }
    _refreshView();
}

void SpriteDirectionPreview::_stopAction ()
{
    _timer.stop();
    _inPlaying = false;
    _currentFrame = 0;
    _refreshView();
}

void SpriteDirectionPreview::_nextAction ()
{
    _currentFrame++;
    _refreshView();
}

void SpriteDirectionPreview::_prevAction ()
{
    _currentFrame--;
    _refreshView();
}

void SpriteDirectionPreview::_lastAction ()
{
    _currentFrame = _direction.nbFrames() - 1;
    _refreshView();
}

void SpriteDirectionPreview::_firstAction ()
{
    _currentFrame = 0;
    _refreshView();
}

void SpriteDirectionPreview::_step ()
{
    _currentFrame++;
    if (_currentFrame >= _direction.nbFrames()) {
        if (_frameOnLoop >= 0) {
            _currentFrame = _frameOnLoop;
        } else {
            _timer.stop();
            _inPlaying = false;
            _currentFrame = _direction.nbFrames() - 1;
        }
    }
    _refreshView();
}

void SpriteDirectionPreview::_originPointChange (bool point)
{
    if (point) {
        _actionOriginCross->blockSignals(true);
        _graphicsView->showOriginPoint(true);
        _actionOriginCross->setChecked(false);
        _actionOriginCross->blockSignals(false);
    } else {
        _graphicsView->showOrigin(false);
    }
}

void SpriteDirectionPreview::_originCrossChange (bool cross)
{
    if (cross) {
        _actionOriginPoint->blockSignals(true);
        _graphicsView->showOriginCross(true);
        _actionOriginPoint->setChecked(false);
        _actionOriginPoint->blockSignals(false);
    } else {
        _graphicsView->showOrigin(false);
    }
}

void SpriteDirectionPreview::_backColorChange (QColor color)
{
    _graphicsView->setBackgroundBrush(color);
}
