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
#include <QSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include "gui/editor/SpriteDirectionEditor.h"

SpriteDirectionEditor::SpriteDirectionEditor ()
{
    setEnabled(false);
    _initWidgets();
    connect(_x, SIGNAL(editingFinished()), this, SLOT(_xChange()));
    connect(_y, SIGNAL(editingFinished()), this, SLOT(_yChange()));
    connect(_width, SIGNAL(editingFinished()), this, SLOT(_widthChange()));
    connect(_height, SIGNAL(editingFinished()), this, SLOT(_heightChange()));
    connect(_originX, SIGNAL(editingFinished()), this, SLOT(_originXChange()));
    connect(_originY, SIGNAL(editingFinished()), this, SLOT(_originYChange()));
    connect(
        _nbFrames, SIGNAL(editingFinished()), this, SLOT(_nbFramesChange())
    );
    connect(
        _nbColumns, SIGNAL(editingFinished()), this, SLOT(_nbColumnsChange())
    );
    connect(_x, SIGNAL(valueChanged(int)), this, SLOT(_directXChange()));
    connect(_y, SIGNAL(valueChanged(int)), this, SLOT(_directYChange()));
    connect(
        _width, SIGNAL(valueChanged(int)), this, SLOT(_directWidthChange())
    );
    connect(
        _height, SIGNAL(valueChanged(int)), this, SLOT(_directHeightChange())
    );
    connect(
        _originX, SIGNAL(valueChanged(int)), this, SLOT(_directOriginXChange())
    );
    connect(
        _originY, SIGNAL(valueChanged(int)), this, SLOT(_directOriginYChange())
    );
    connect(
        _nbFrames, SIGNAL(valueChanged(int)),
        this, SLOT(_directNbFramesChange())
    );
    connect(
        _nbColumns, SIGNAL(valueChanged(int)),
        this, SLOT(_directNbColumnsChange())
    );
}

SpriteDirection SpriteDirectionEditor::direction () const
{
    return _direction;
}

void SpriteDirectionEditor::setDirection (const SpriteDirection &direction)
{
    _blockSignals(true);
    _direction = direction;
    _refreshWidgets(direction);
    _blockSignals(false);
}

void SpriteDirectionEditor::_initWidgets ()
{
    _x = new QSpinBox;
    _y = new QSpinBox;
    _width = new QSpinBox;
    _height = new QSpinBox;
    _originX = new QSpinBox;
    _originY = new QSpinBox;
    _nbFrames = new QSpinBox;
    _nbColumns = new QSpinBox;

    _x->setRange(0, 9999);
    _y->setRange(0, 9999);
    _width->setRange(1, 9999);
    _height->setRange(1, 9999);
    _originX->setRange(-4999, 4999);
    _originY->setRange(-4999, 4999);
    _nbFrames->setRange(1, 999);
    _nbColumns->setRange(1, 999);

    _x->setSingleStep(8);
    _y->setSingleStep(8);
    _width->setSingleStep(8);
    _height->setSingleStep(8);
    _originX->setSingleStep(4);
    _originY->setSingleStep(4);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("X:")), 0, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_x, 0, 1);
    layout->addWidget(new QLabel(tr("Y:")), 1, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_y, 1, 1);
    layout->addWidget(new QLabel(tr("Width:")), 2, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_width, 2, 1);
    layout->addWidget(new QLabel(tr("Height:")), 3, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_height, 3, 1);
    layout->addWidget(new QLabel(tr("Origin x:")), 0, 2, 1, 1, Qt::AlignRight);
    layout->addWidget(_originX, 0, 3);
    layout->addWidget(new QLabel(tr("Origin y:")), 1, 2, 1, 1, Qt::AlignRight);
    layout->addWidget(_originY, 1, 3);

    layout->addWidget(
        new QLabel(tr("Number of frames:")), 2, 2, 1, 1, Qt::AlignRight
    );
    layout->addWidget(_nbFrames, 2, 3);
    layout->addWidget(
        new QLabel(tr("Number of columns:")), 3, 2, 1, 1, Qt::AlignRight
    );
    layout->addWidget(_nbColumns, 3, 3);
    setLayout(layout);
}

void SpriteDirectionEditor::_refreshWidgets (const SpriteDirection &direction)
{
    _x->setValue(direction.x());
    _y->setValue(direction.y());
    _width->setValue(direction.width());
    _height->setValue(direction.height());
    _originX->setValue(direction.originX());
    _originX->setMaximum(direction.width());
    _originY->setValue(direction.originY());
    _originY->setMaximum(direction.height());
    _nbFrames->setValue(direction.nbFrames());
    _nbColumns->setValue(direction.nbColumns());
}

void SpriteDirectionEditor::_blockSignals (bool block)
{
    _x->blockSignals(block);
    _y->blockSignals(block);
    _width->blockSignals(block);
    _height->blockSignals(block);
    _originX->blockSignals(block);
    _originY->blockSignals(block);
    _nbFrames->blockSignals(block);
    _nbColumns->blockSignals(block);
}

void SpriteDirectionEditor::_xChange ()
{
    int x = _x->value();
    if (x != _direction.x()) {
        _direction.setX(x);
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_yChange ()
{
    int y = _y->value();
    if (y != _direction.y()) {
        _direction.setY(y);
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_widthChange ()
{
    int width = _width->value();
    if (width != _direction.width()) {
        _direction.setWidth(width);
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_heightChange ()
{
    int height = _height->value();
    if (height != _direction.height()) {
        _direction.setHeight(height);
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_originXChange ()
{
    int oX = _originX->value();
    if (oX != _direction.originX()) {
        _direction.setOriginX(oX);
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_originYChange ()
{
    int oY = _originY->value();
    if (oY != _direction.originY()) {
        _direction.setOriginY(_originY->value());
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_nbFramesChange ()
{
    int nbFrames = _nbFrames->value();
    if (nbFrames != _direction.nbFrames()) {
        _direction.setNbFrames(_nbFrames->value());
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_nbColumnsChange ()
{
    int nbColumns = _nbColumns->value();
    if (nbColumns != _direction.nbColumns()) {
        _direction.setNbColumns(_nbColumns->value());
        emit directionChange(_direction);
    }
}

void SpriteDirectionEditor::_directXChange ()
{
    SpriteDirection direction = _direction;
    direction.setX(_x->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directYChange ()
{
    SpriteDirection direction = _direction;
    direction.setY(_y->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directWidthChange ()
{
    SpriteDirection direction = _direction;
    direction.setWidth(_width->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directHeightChange ()
{
    SpriteDirection direction = _direction;
    direction.setHeight(_height->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directOriginXChange ()
{
    SpriteDirection direction = _direction;
    direction.setOriginX(_originX->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directOriginYChange ()
{
    SpriteDirection direction = _direction;
    direction.setOriginY(_originY->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directNbFramesChange ()
{
    SpriteDirection direction = _direction;
    direction.setNbFrames(_nbFrames->value());
    emit directDirectionChange(direction);
}

void SpriteDirectionEditor::_directNbColumnsChange ()
{
    SpriteDirection direction = _direction;
    direction.setNbColumns(_nbColumns->value());
    emit directDirectionChange(direction);
}
