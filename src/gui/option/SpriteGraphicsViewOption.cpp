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
#include <QSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include "gui/option/SpriteGraphicsViewOption.h"
#include "gui/graphics/SpriteGraphicsView.h"
#include "gui/widget/ColorButton.h"

SpriteGraphicsViewOption::SpriteGraphicsViewOption (
    SpriteGraphicsView *view
) :
    _mustDelete(false)
{
    _initWidgets();
    if (view == 0) {
        view = new SpriteGraphicsView;
        _mustDelete = true;
    }
    _view = view;
    _refreshWidgets(view);
}

SpriteGraphicsViewOption::~SpriteGraphicsViewOption ()
{
    if (_mustDelete) {
        delete _view;
    }
}

void SpriteGraphicsViewOption::setSettings ()
{
    _view->setShowSceneBorder(_showSceneBorder->isChecked());
    _view->setBackgroundBrush(_backColor->color());
    _view->setZoom(_zoom->itemData(_zoom->currentIndex()).toFloat());
    _view->setShowGrid(_showGrid->isChecked());
    _view->setSnap(_snap->isChecked());
    _view->setGridColor(_gridColor->color());
    _view->setGridOpacity((float)_gridOpacity->value() / 100);
    _view->setGridWidth(_gridWidth->value());
    _view->setGridHeight(_gridHeight->value());
    _view->setDisplaySelectionShadow(_displaySelectionShadow->isChecked());
    _view->setSelectionColor(_selectionColor->color());
}

void SpriteGraphicsViewOption::save ()
{
    _view->saveSettings();
}

void SpriteGraphicsViewOption::_initWidgets ()
{
    _showSceneBorder = new QCheckBox(tr("Show scene border"));
    _backColor = new ColorButton;
    _zoom = new QComboBox;
    _showGrid = new QGroupBox(tr("Show grid"));
    _snap = new QCheckBox(tr("Snap to grid"));
    _gridColor = new ColorButton;
    _gridOpacity = new QSpinBox;
    _gridWidth = new QSpinBox;
    _gridHeight = new QSpinBox;
    _displaySelectionShadow = new QCheckBox(tr("Display selection shadow"));
    _selectionColor = new ColorButton;

    _zoom->addItem("800%", 8.0);
    _zoom->addItem("400%", 4.0);
    _zoom->addItem("200%", 2.0);
    _zoom->addItem("100%", 1.0);
    _zoom->addItem("50%", 0.5);
    _zoom->addItem("25%", 0.25);
    _showGrid->setStyleSheet("QGroupBox::title{font-bold:false}");
    _showGrid->setFlat(true);
    _showGrid->setCheckable(true);
    _gridOpacity->setMaximum(100);
    _gridOpacity->setSuffix("%");
    _gridWidth->setMinimum(1);
    _gridWidth->setSingleStep(8);
    _gridHeight->setMinimum(1);
    _gridHeight->setSingleStep(8);

    QFormLayout *styleLayout = new QFormLayout;
    styleLayout->addRow(tr("Color:"), _gridColor);
    styleLayout->addRow(tr("Opacity:"), _gridOpacity);
    styleLayout->setAlignment(_gridColor, Qt::AlignCenter);
    styleLayout->setLabelAlignment(Qt::AlignRight);
    _showGrid->setLayout(styleLayout);

    QGroupBox *gridGroup = new QGroupBox(tr("Grid"));
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(_snap, 0, 0, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(new QLabel(tr("Width:")), 1, 0, 1, 1, Qt::AlignRight);
    gridLayout->addWidget(_gridWidth, 1, 1);
    gridLayout->addWidget(
        new QLabel(tr("Height:")), 2, 0, 1, 1, Qt::AlignRight
    );
    gridLayout->addWidget(_gridHeight, 2, 1);
    gridLayout->addWidget(_showGrid, 0, 3, 3, 1);
    gridLayout->setColumnMinimumWidth(2, 15);
    gridGroup->setLayout(gridLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_showSceneBorder, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(
        new QLabel(tr("Background color:")), 1, 0, 1, 1, Qt::AlignRight
    );
    layout->addWidget(_backColor, 1, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(
        new QLabel(tr("Zoom:")), 2, 0, 1, 1, Qt::AlignRight
    );
    layout->addWidget(_zoom, 2, 1);
    layout->addWidget(
        new QLabel(tr("Selection color:")), 0, 3, 1, 1, Qt::AlignRight
    );
    layout->addWidget(_selectionColor, 0, 4);
    layout->addWidget(_displaySelectionShadow, 1, 3, 1, 2, Qt::AlignCenter);
    layout->addWidget(gridGroup, 3, 0, 1, 5, Qt::AlignCenter);
    layout->setColumnMinimumWidth(2, 15);
    setLayout(layout);
}

void SpriteGraphicsViewOption::_refreshWidgets (const SpriteGraphicsView *view)
{
    _showSceneBorder->setChecked(view->showSceneBorder());
    _backColor->setColor(view->backgroundBrush().color());
    _zoom->setCurrentIndex(_zoom->findData(view->zoom()));
    _showGrid->setChecked(view->showGrid());
    _snap->setChecked(view->snap());
    _gridColor->setColor(view->gridColor());
    _gridOpacity->setValue(view->gridOpacity() * 100);
    _gridWidth->setValue(view->gridWidth());
    _gridHeight->setValue(view->gridHeight());
    _displaySelectionShadow->setChecked(view->displaySelectionShadow());
    _selectionColor->setColor(view->selectionColor());
}
