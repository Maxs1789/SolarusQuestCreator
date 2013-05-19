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
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QFormLayout>
#include "gui/option/SpritePreviewOption.h"
#include "gui/graphics/SpriteDirectionGraphicsView.h"
#include "gui/widget/ColorButton.h"

SpritePreviewOption::SpritePreviewOption (SpriteDirectionGraphicsView *view) :
    _mustDelete(false)
{
    _initWidgets();
    if (view == 0) {
        view = new SpriteDirectionGraphicsView;
        _mustDelete = true;
    }
    _view = view;
    _refreshWidgets(_view);
}

SpritePreviewOption::~SpritePreviewOption ()
{
    if (_mustDelete) {
        delete _view;
    }
}

void SpritePreviewOption::setSettings ()
{
    _view->setBackgroundBrush(_backColor->color());
    _view->setZoom(_zoom->itemData(_zoom->currentIndex()).toFloat());
    _view->showOrigin(_originGroup->isChecked());
    _view->setSelectionColor(_originColor->color());
    if (_originGroup->isChecked()) {
        _view->showOriginCross(
            _originMode->itemData(_originMode->currentIndex()).toBool()
        );
    }
}

void SpritePreviewOption::save ()
{
    _view->saveSettings();
}

void SpritePreviewOption::_initWidgets ()
{
    _backColor = new ColorButton;
    _zoom = new QComboBox;
    _originGroup = new QGroupBox(tr("Show origin"));
    _originColor = new ColorButton;
    _originMode = new QComboBox;

    _zoom->addItem("800%", 8.0);
    _zoom->addItem("400%", 4.0);
    _zoom->addItem("200%", 2.0);
    _zoom->addItem("100%", 1.0);
    _zoom->addItem("50%", 0.5);
    _zoom->addItem("25%", 0.25);
    _originGroup->setStyleSheet("QGroupBox::title{font-bold:false}");
    _originGroup->setFlat(true);
    _originGroup->setCheckable(true);
    _originMode->addItem(tr("point"), false);
    _originMode->addItem(tr("cross"), true);

    QFormLayout *originLayout = new QFormLayout;
    originLayout->addRow(tr("Color:"), _originColor);
    originLayout->addRow(tr("Mode:"), _originMode);
    originLayout->setAlignment(_originColor, Qt::AlignCenter);
    originLayout->setLabelAlignment(Qt::AlignRight);
    _originGroup->setLayout(originLayout);

    QFormLayout *baseLayout = new QFormLayout;
    baseLayout->addRow(tr("Background color:"), _backColor);
    baseLayout->addRow(tr("Zoom:"), _zoom);
    baseLayout->setAlignment(_backColor, Qt::AlignCenter);
    baseLayout->setLabelAlignment(Qt::AlignRight);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(baseLayout);
    layout->addWidget(_originGroup);
    setLayout(layout);
}

void SpritePreviewOption::_refreshWidgets (
    const SpriteDirectionGraphicsView *view
) {
    _backColor->setColor(view->backgroundBrush().color());
    _zoom->setCurrentIndex(_zoom->findData(view->zoom()));
    _originGroup->setChecked(view->showOrigin());
    _originColor->setColor(view->selectionColor());
    _originMode->setCurrentIndex(_originMode->findData(view->cross()));
}
