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
#include <QLineEdit>
#include <QSpinBox>
#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QStackedWidget>
#include "gui/editor/SpriteAnimationEditor.h"
#include "gui/editor/SpriteDirectionEditor.h"
#include "sol/Quest.h"
#include "sol/Sprite.h"
#include "gui/dialog/ImageFinder.h"
#include "gui/widget/TilesetComboBox.h"

SpriteAnimationEditor::SpriteAnimationEditor (Quest *quest) :
    _quest(quest),
    _directory(quest->dataDirectory() + "sprites/")
{
    setEnabled(false);
    _initWidgets();
    connect(_imageButton, SIGNAL(clicked()), this, SLOT(_findImage()));
    connect(
        _frameDelay, SIGNAL(editingFinished()), this, SLOT(_frameDelayChange())
    );
    connect(
        _frameOnLoop, SIGNAL(editingFinished()),
        this, SLOT(_frameOnLoopChange())
    );
    connect(_imageFinder, SIGNAL(accepted()), this, SLOT(_imageChange()));
    connect(
        _tilesetComboBox, SIGNAL(currentIndexChanged(int)),
        this, SLOT(_tilesetChange())
    );
    connect(
        _frameDelay, SIGNAL(valueChanged(int)),
        this, SLOT(_directFrameDelayChange())
    );
    connect(
        _frameOnLoop, SIGNAL(valueChanged(int)),
        this, SLOT(_directFrameOnLoopChange())
    );
}

SpriteAnimation SpriteAnimationEditor::animation () const
{
    return _animation;
}

QString SpriteAnimationEditor::tileset () const
{
    int n = _tilesetComboBox->currentIndex();
    return _tilesetComboBox->itemData(n).toString();
}

void SpriteAnimationEditor::setAnimation (const SpriteAnimation &animation)
{
    _blockSignals(true);
    _animation = animation;
    _refreshWidgets(animation);
    _blockSignals(false);
}

void SpriteAnimationEditor::_initWidgets ()
{
    _image = new QLineEdit;
    _frameDelay = new QSpinBox;
    _frameOnLoop = new QSpinBox;
    _imageButton = new QPushButton("...");
    _imageFinder = new ImageFinder(this, _directory);
    _tilesetComboBox = new TilesetComboBox(_quest);

    _image->setEnabled(false);
    _frameOnLoop->setMinimum(-1);
    _frameDelay->setMaximum(10000);
    _imageButton->setToolTip(tr("Change image"));
    _imageButton->setMaximumSize(24, 24);

    _frameDelay->setSingleStep(50);

    _imageWidget = new QStackedWidget;
    _imageWidget->addWidget(_image);
    _imageWidget->addWidget(_tilesetComboBox);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->addRow(tr("Frame delay:"), _frameDelay);
    formLayout->addRow(tr("Frame on loop:"), _frameOnLoop);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Image:")), 0, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(_imageWidget, 0, 1);
    layout->addWidget(_imageButton, 0, 2, 1, 1, Qt::AlignVCenter);
    layout->addLayout(formLayout, 1, 0, 1, 3);
    setLayout(layout);
}

void SpriteAnimationEditor::_refreshWidgets (const SpriteAnimation &animation)
{
    _image->setText(animation.image());
    _frameDelay->setValue(animation.frameDelay());
    _frameOnLoop->setEnabled(animation.frameDelay() > 0);
    _frameOnLoop->setValue(animation.frameOnLoop());
    _frameOnLoop->setMaximum(animation.maxNbFrames() - 1);
    if (animation.image() == "tileset") {
        _imageWidget->setCurrentIndex(_imageWidget->indexOf(_tilesetComboBox));
    } else {
        _imageWidget->setCurrentIndex(_imageWidget->indexOf(_image));
    }
}

void SpriteAnimationEditor::_blockSignals (bool block)
{
    _image->blockSignals(block);
    _frameDelay->blockSignals(block);
    _frameOnLoop->blockSignals(block);
}

void SpriteAnimationEditor::_imageChange ()
{
    QString image = _imageFinder->image();
    image.replace(_directory, "");
    _image->setText(image);
    if (image != _animation.image()) {
        _animation.setImage(image);
        emit animationChange(_animation);
    }
}

void SpriteAnimationEditor::_frameDelayChange ()
{
    if (_frameDelay->value() != _animation.frameDelay()) {
        _animation.setFrameDelay(_frameDelay->value());
        emit animationChange(_animation);
    }
}

void SpriteAnimationEditor::_frameOnLoopChange ()
{
    if (_frameOnLoop->value() != _animation.frameOnLoop()) {
        _animation.setFrameOnLoop(_frameOnLoop->value());
        emit animationChange(_animation);
    }
}

void SpriteAnimationEditor::_findImage ()
{
    _imageFinder->show();
    _imageFinder->raise();
    _imageFinder->activateWindow();
}

void SpriteAnimationEditor::_tilesetChange ()
{
    emit tilesetChange();
}

void SpriteAnimationEditor::_directFrameDelayChange ()
{
    SpriteAnimation animation = _animation;
    animation.setFrameDelay(_frameDelay->value());
    emit directAnimationChange(animation);
}

void SpriteAnimationEditor::_directFrameOnLoopChange ()
{
    SpriteAnimation animation = _animation;
    animation.setFrameOnLoop(_frameOnLoop->value());
    emit directAnimationChange(animation);
}
