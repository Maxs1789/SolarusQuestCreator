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
#include <QTreeWidget>
#include <QGraphicsView>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include "gui/dialog/ImageFinder.h"
#include "util/FileTools.h"

ImageFinder::ImageFinder (QWidget *parent, QString directory) :
    QDialog(parent)
{
    setWindowTitle(tr("Open image"));
    setMinimumSize(800, 480);
    setModal(true);
    _initWidgets();
    QTreeWidgetItem *item = new QTreeWidgetItem(1);
    item->setText(0, "tileset");
    item->setData(0, QTreeWidgetItem::UserType, "tileset");
    item->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));
    _treeWidget->addTopLevelItem(item);
    _loadImages(directory);
    item->setSelected(true);
    connect(
        _treeWidget,
        SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
        this, SLOT(_imageChange())
    );
    connect(
        _treeWidget, SIGNAL(doubleClicked(QModelIndex)),
        this, SLOT(_doubleClick())
    );
    connect(_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QString ImageFinder::image () const
{
    return _image;
}

void ImageFinder::_initWidgets ()
{
    _treeWidget = new QTreeWidget;
    _graphicsView = new QGraphicsView;
    _buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );

    _treeWidget->setHeaderHidden(true);

    _graphicsView->setBackgroundBrush(QBrush(Qt::lightGray));
    _graphicsView->setScene(new QGraphicsScene());

    QHBoxLayout *baseLayout = new QHBoxLayout;
    baseLayout->addWidget(_treeWidget);
    baseLayout->addWidget(_graphicsView, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(baseLayout);
    layout->addWidget(_buttonBox);

    setLayout(layout);
}

void ImageFinder::_loadImages (QString directory, QTreeWidgetItem *treeItem)
{
    QDir dir(directory);
    if (dir.exists()) {
        QFileInfoList list = dir.entryInfoList(
            QStringList("*.png"), QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot, QDir::DirsFirst
        );
        QList<QTreeWidgetItem *> items;
        for (int i = 0; i < list.size(); i++) {
            QFileInfo info(list[i].filePath());
            if (info.exists()) {
                if (info.isDir()) {
                    QTreeWidgetItem *item = new QTreeWidgetItem(0);
                    _loadImages(list[i].absoluteFilePath(), item);
                    if (item->childCount() > 0) {
                        item->setText(0, list[i].fileName());
                        item->setIcon(
                            0, style()->standardIcon(QStyle::SP_DirIcon)
                        );
                        items.push_back(item);
                    }
                } else {
                    QTreeWidgetItem *item = new QTreeWidgetItem(1);
                    item->setText(0, list[i].fileName());
                    item->setData(
                        0, QTreeWidgetItem::UserType, list[i].absoluteFilePath()
                    );
                    item->setIcon(
                        0, style()->standardIcon(QStyle::SP_FileIcon)
                    );
                    items.push_back(item);
                }
            }
        }
        if (treeItem != 0) {
            treeItem->addChildren(items);
        } else {
            _treeWidget->addTopLevelItems(items);
        }
    }
}

void ImageFinder::_imageChange ()
{
    QTreeWidgetItem *item = _treeWidget->currentItem();
    if (item->type() == 1) {
        _buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        _image = item->data(0, QTreeWidgetItem::UserType).toString();
        QPixmap pix(_image);
        _graphicsView->scene()->clear();
        _graphicsView->scene()->addItem(new QGraphicsPixmapItem(pix));
        _graphicsView->scene()->setSceneRect(pix.rect());
    }
}

void ImageFinder::_doubleClick ()
{
    QTreeWidgetItem *item = _treeWidget->currentItem();
    if (item->type() == 1) {
        accept();
    }
}
