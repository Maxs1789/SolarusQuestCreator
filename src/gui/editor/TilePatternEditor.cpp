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
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QFormLayout>
#include "gui/editor/TilePatternEditor.h"

TilePatternEditor::TilePatternEditor (const TilePattern &tile) :
    _tile(tile)
{
    _initWidgets();
    if (tile.id() < 0) {
        this->setEnabled(false);
    }
    _refreshWidgets(tile);
    connect(
        _ground, SIGNAL(currentIndexChanged(int)), this, SLOT(_groundChange())
    );
    connect(
        _layer, SIGNAL(currentIndexChanged(int)), this, SLOT(_layerChange())
    );
    connect(
        _scrolling, SIGNAL(currentIndexChanged(int)),
        this, SLOT(_scrollingChange())
    );
    connect(
        _animated, SIGNAL(toggled(bool)), this, SLOT(_animationChange())
    );
    connect(
        _direction, SIGNAL(currentIndexChanged(int)),
        this, SLOT(_animationChange())
    );
    connect(
        _sequence, SIGNAL(currentIndexChanged(int)),
        this, SLOT(_animationChange())
    );
}

TilePattern TilePatternEditor::tile () const
{
    return _tile;
}

void TilePatternEditor::setTile (const TilePattern &tile)
{
    _tile = tile;
    setEnabled(tile.id() >= 0);
    _blockSignals(true);
    _refreshWidgets(tile);
    _blockSignals(false);
}

void TilePatternEditor::_initWidgets ()
{
    _id = new QLabel;
    _position = new QLabel;
    _dimension = new QLabel;
    _ground = new QComboBox;
    _layer = new QComboBox;
    _scrolling = new QComboBox;
    _animated = new QCheckBox;
    _direction = new QComboBox;
    _sequence = new QComboBox;

    _ground->addItem(
        QIcon(":ground/traversable"), tr("traversable"), TRAVERSABLE
    );
    _ground->addItem(QIcon(":ground/wall"), tr("wall"), WALL);
    _ground->addItem(
        QIcon(":ground/wall_top_right"), tr("wall top-right"), WALL_TOP_RIGHT
    );
    _ground->addItem(
        QIcon(":ground/wall_top_left"), tr("wall top-left"), WALL_TOP_LEFT
    );
    _ground->addItem(
        QIcon(":ground/wall_bottom_left"),
        tr("wall bottom-left"), WALL_BOTTOM_LEFT
    );
    _ground->addItem(
        QIcon(":ground/wall_bottom_right"),
        tr("wall bottom-right"), WALL_BOTTOM_RIGHT
    );
    _ground->addItem(QIcon(":ground/empty"), tr("empty"), EMPTY);
    _ground->addItem(
        QIcon(":ground/water_top_right"), tr("water top-right"), WATER_TOP_RIGHT
    );
    _ground->addItem(
        QIcon(":ground/water_top_left"), tr("water top-left"), WATER_TOP_LEFT
    );
    _ground->addItem(
        QIcon(":ground/water_bottom_left"),
        tr("water bottom-left"), WATER_BOTTOM_LEFT
    );
    _ground->addItem(
        QIcon(":ground/water_bottom_right"),
        tr("water bottom-right"), WATER_BOTTOM_RIGHT
    );
    _ground->addItem(QIcon(":ground/deep_water"), tr("deep water"), DEEP_WATER);
    _ground->addItem(
        QIcon(":ground/shallow_water"), tr("shallow water"), SHALLOW_WATER
    );
    _ground->addItem(QIcon(":ground/hole"), tr("hole"), HOLE);
    _ground->addItem(QIcon(":ground/ladder"), tr("ladder"), LADDER);
    _ground->addItem(QIcon(":ground/prickles"), tr("prickles"), PRICKLES);
    _ground->addItem(QIcon(":ground/lava"), tr("lava"), LAVA);

    _layer->addItem(QIcon(":layer/low"), tr("low"), LOW);
    _layer->addItem(
        QIcon(":layer/intermediate"), tr("intermediate"), INTERMEDIATE
    );
    _layer->addItem(QIcon(":layer/high"), tr("high"), HIGH);

    _scrolling->addItem(QIcon(":other/none"), tr("no scrolling"), NO_SCROLLING);
    _scrolling->addItem(QIcon(":scrolling/self"), tr("self"), SELF);
    _scrolling->addItem(QIcon(":scrolling/parallax"), tr("parallax"), PARALLAX);

    _direction->addItem(QIcon(":direction/horizontal"), tr("horizontal"), 0);
    _direction->addItem(QIcon(":direction/vertical"), tr("vertical"), 1);

    _sequence->addItem(QIcon(":sequence/0120"), tr("0-1-2-..."), false);
    _sequence->addItem(QIcon(":sequence/01210"), tr("0-1-2-1-..."), true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Id:")), 0, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_id, 0, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(new QLabel(tr("Position:")), 1, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_position, 1, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(new QLabel(tr("Dimension:")), 2, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_dimension, 2, 1, 1, 1, Qt::AlignCenter);

    layout->addWidget(new QLabel(tr("Ground:")), 0, 3, 1, 1, Qt::AlignRight);
    layout->addWidget(_ground, 0, 4);
    layout->addWidget(new QLabel(tr("Layer:")), 1, 3, 1, 1, Qt::AlignRight);
    layout->addWidget(_layer, 1, 4);
    layout->addWidget(new QLabel(tr("Scrolling:")), 2, 3, 1, 1, Qt::AlignRight);
    layout->addWidget(_scrolling, 2, 4);

    layout->addWidget(_animated, 0, 6, 1, 1, Qt::AlignRight);
    layout->addWidget(new QLabel(tr("Animated")), 0, 7);
    layout->addWidget(new QLabel(tr("Direction:")), 1, 6, 1, 1, Qt::AlignRight);
    layout->addWidget(_direction, 1, 7);
    layout->addWidget(new QLabel(tr("Sequence:")), 2, 6, 1, 1, Qt::AlignRight);
    layout->addWidget(_sequence, 2, 7);

    layout->setColumnMinimumWidth(1, 100);
    layout->setColumnMinimumWidth(2, 15);
    layout->setColumnMinimumWidth(5, 15);
    setLayout(layout);
}

void TilePatternEditor::_refreshWidgets(const TilePattern &tile)
{
    _id->setText(QString("<b>") + QString::number(tile.id()) + "</b>");
    _position->setText(
        QString("<b>") + QString::number(tile.x()) +
        "</b>, <b>" + QString::number(tile.y()) + "</b>"
    );
    _dimension->setText(
        QString("<b>") + QString::number(tile.width()) +
        "</b>x<b>" + QString::number(tile.height()) + "</b>"
    );
    _ground->setCurrentIndex(_ground->findData(tile.ground()));
    _layer->setCurrentIndex(_layer->findData(tile.defaultLayer()));
    _scrolling->setCurrentIndex(_scrolling->findData(tile.scrolling()));
    _animated->setChecked(tile.isAnimated());
    _direction->setEnabled(tile.isAnimated());
    _sequence->setEnabled(tile.isAnimated());
    int dir = 0;
    if (tile.isAnimated()) {
        int x = tile.x(), x2 = tile.x2();
        dir = x == x2 ? 1 : 0;
    }
    _direction->setCurrentIndex(_direction->findData(dir));
    _sequence->setCurrentIndex(_sequence->findData(tile.isSeq0121()));
}

void TilePatternEditor::_blockSignals (bool block)
{
    _ground->blockSignals(block);
    _layer->blockSignals(block);
    _scrolling->blockSignals(block);
    _animated->blockSignals(block);
    _direction->blockSignals(block);
    _sequence->blockSignals(block);
}

void TilePatternEditor::_groundChange ()
{
    _tile.setGround((Ground)_ground->itemData(_ground->currentIndex()).toInt());
    emit tileChange(_tile);
}

void TilePatternEditor::_layerChange ()
{
    _tile.setDefaultLayer(
        (Layer)_layer->itemData(_layer->currentIndex()).toInt()
    );
    emit tileChange(_tile);
}

void TilePatternEditor::_scrollingChange ()
{
    _tile.setScrolling(
        (Scrolling)_scrolling->itemData(_scrolling->currentIndex()).toInt()
    );
    emit tileChange(_tile);
}

void TilePatternEditor::_animationChange ()
{
    bool animated = _animated->isChecked();
    _direction->setEnabled(animated);
    _sequence->setEnabled(animated);
    int x = _tile.x(), y = _tile.y();
    if (animated) {
        bool seq0121 = _sequence->itemData(_sequence->currentIndex()).toBool();
        int dir = _direction->itemData(_direction->currentIndex()).toInt();
        if (dir == 0) {
            int w = _tile.width();
            int x2 = x + w, x3 = x2 + w;
            _tile.setPositions(x, y, x2, y, x3, y, seq0121);
        } else {
            int h = _tile.height();
            int y2 = y + h, y3 = y2 + h;
            _tile.setPositions(x, y, x, y2, x, y3, seq0121);
        }
    } else {
        _tile.setPosition(x, y);
    }
    emit tileChange(_tile);
}
