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
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QGraphicsView>
#include "gui/editor/TilesetEditor.h"
#include "gui/editor/TilePatternEditor.h"
#include "gui/widget/TilePatternListWidget.h"

#include <QDebug>

TilesetEditor::TilesetEditor (const Tileset &tileset) :
    _tileset(new Tileset(""))
{
    _initWidgets();
    *_tileset = tileset;
    _tilePatternTable->setTileset(_tileset);
    _name->setText(_tileset->name());
    connect(_name, SIGNAL(editingFinished()), this, SLOT(_nameChange()));
    QList<TilePattern> list = _tileset->allPatterns();
    for (int i = 0; i < list.size(); i++) {
        qDebug() << list[i].toLua();
    }
}

Tileset TilesetEditor::tileset ()
{
    return _tileset->copy();
}

void TilesetEditor::setTileset (const Tileset &tileset)
{
    *_tileset = tileset;
}

void TilesetEditor::refreshSelection (QList<int> selection)
{

}

void TilesetEditor::refreshPattern (int id)
{

}

void TilesetEditor::addPatterns (QList<int> selection)
{

}

void TilesetEditor::removePatterns (QList<int> selection)
{

}

void TilesetEditor::_initWidgets ()
{
    _id = new QLabel;
    _name = new QLineEdit;
    _image = new QLineEdit;
    _editImage = new QPushButton(tr("edit"));
    _tilePatternTable = new TilePatternListWidget;

    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(_image);
    imageLayout->addWidget(_editImage);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->addRow(tr("Id:"), _id);
    formLayout->addRow(tr("Name:"), _name);
    formLayout->addRow(tr("Image:"), imageLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(formLayout);
    leftLayout->addWidget(_tilePatternTable);

    QGridLayout *layout = new QGridLayout;
    layout->addLayout(leftLayout, 0, 0, 2, 1);
    layout->addWidget(new QGraphicsView(), 0, 1);
    layout->addWidget(new TilePatternEditor(TilePattern(42)), 1, 1);

    layout->setColumnStretch(1, 1);
    setLayout(layout);
}

void TilesetEditor::_nameChange ()
{
    _tileset->setName(_name->text());
    emit tilesetChange(_tileset->copy());
}
