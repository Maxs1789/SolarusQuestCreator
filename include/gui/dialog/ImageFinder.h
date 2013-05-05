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
#ifndef IMAGE_FINDER_H
#define IMAGE_FINDER_H

#include <QDialog>

class QTreeWidget;
class QTreeWidgetItem;
class QGraphicsView;
class QDialogButtonBox;

class ImageFinder : public QDialog
{
    Q_OBJECT
public:
    ImageFinder (QWidget *parent, QString directory);

    QString image () const;

private:
    QTreeWidget *_treeWidget;
    QGraphicsView *_graphicsView;
    QDialogButtonBox *_buttonBox;
    QString _image;

    void _initWidgets ();
    void _loadImages (QString directory, QTreeWidgetItem *treeItem = 0);

private slots:
    void _imageChange ();
    void _doubleClick ();
};

#endif
