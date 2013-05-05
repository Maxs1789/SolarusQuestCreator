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
#ifndef TILESET_EDITOR_H
#define TILESET_EDITOR_H

#include <QWidget>
#include "sol/Tileset.h"

class QLabel;
class QLineEdit;
class QPushButton;
class TilePatternListWidget;

class TilesetEditor : public QWidget, public TilesetView
{
    Q_OBJECT
public:
    TilesetEditor (const Tileset &tileset);

    Tileset tileset ();

    void setTileset (const Tileset &tileset);

    void simpleRefresh (QString message) {}
    void refreshSelection (QList<int> selection);
    void refreshPattern (int id);
    void addPatterns (QList<int> selection);
    void removePatterns (QList<int> selection);

signals:
    void tilesetChange (Tileset tileset);

private:
    Tileset *_tileset;
    QLabel *_id;
    QLineEdit *_name;
    QLineEdit *_image;
    QPushButton *_editImage;
    //_backgroundColor;
    TilePatternListWidget *_tilePatternTable;

    void _initWidgets ();

private slots:
    void _nameChange ();
};

#endif
