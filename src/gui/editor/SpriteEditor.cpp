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
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QListWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include "gui/widget/SQCGraphicsView.h"
#include "gui/editor/SpriteEditor.h"
#include "gui/editor/SpriteAnimationEditor.h"
#include "gui/editor/SpriteDirectionEditor.h"
#include "sol/Quest.h"
#include "sol/SpriteAnimation.h"
#include "gui/dialog/ImageFinder.h"
#include "gui/widget/SpriteDirectionPreview.h"

SpriteEditor::SpriteEditor (Quest *quest, const Sprite &sprite) :
    Editor(quest->directory(), SPRITE, sprite.id()),
    _quest(quest),
    _sprite(new Sprite(""))
{
    *_sprite = sprite;
    _sprite->attach(this);
    _initWidgets();
    _refreshWidgets();
    try {
        _sprite->setSelection(_animations->currentText());
    } catch (const SQCException &ex) {}
    _connects();
}

SpriteEditor::~SpriteEditor ()
{
    delete _sprite;
}

Sprite *SpriteEditor::sprite()
{
    return _sprite;
}

void SpriteEditor::simpleRefresh (QString message)
{
    if (message == Sprite::p_name) {
        _name->blockSignals(true);
        _name->setText(_sprite->name());
        _name->blockSignals(false);
        _refreshTitle();
    }
}

void SpriteEditor::refreshSelection (const SpriteSelection &selection)
{
    if (!selection.isEmpty()) {
        int n = _animations->findText(selection.animation());
        _animations->blockSignals(true);
        _animationEditor->setEnabled(true);
        _animations->setEnabled(true);
        _animations->setCurrentIndex(n);
        _animations->blockSignals(false);
        refreshAnimation(selection.animation());
    } else if (_sprite->animationNames().size() == 0) {
        _animationEditor->setEnabled(false);
        _animations->setEnabled(false);
    }
    _removeAnimationButton->setEnabled(!selection.isEmpty());
}

void SpriteEditor::refreshAnimation (const QString &name)
{
    _refreshTitle();
    SpriteAnimation animation = _sprite->animation(name);
    QString img_path = animation.image();
    if (img_path == "tileset") {
        img_path = _quest->dataDirectory() + "tilesets/";
        img_path += _animationEditor->tileset() + ".entities.png";
    } else {
        img_path = _quest->dataDirectory() + "sprites/" + img_path;
    }
    QPixmap img(img_path);
    _graphicsView->scene()->clear();
    _graphicsView->scene()->addItem(new QGraphicsPixmapItem(img));
    _graphicsView->scene()->setSceneRect(img.rect());
    SpriteSelection selection = _sprite->selection();
    if (!selection.isEmpty() && selection.animation() == name) {
        _animationGroup->setEnabled(true);
        _directions->setEnabled(true);
        _animationEditor->setAnimation(animation);
        _directions->blockSignals(true);
        _directions->clear();
        int mw = 16, mh = 16;
        for (int i = 0; i < animation.countDirections(); i++) {
            SpriteDirection direction = animation.direction(i);
            QPixmap pix = img.copy(
                direction.x(), direction.y(),
                direction.width(), direction.height()
            );
            if (pix.width() > mw) {
                mw = pix.width();
            }
            if (pix.height() > mh) {
                mh = pix.height();
            }
            QString str = QString::number(i);
            switch (i) {
            case 0: str += tr(" - right"); break;
            case 1: str += tr(" - up"); break;
            case 2: str += tr(" - left"); break;
            case 3: str += tr(" - down"); break;
            }
            QListWidgetItem *item = new QListWidgetItem(QIcon(pix), str);
            item->setData(QListWidgetItem::UserType, i);
            _directions->addItem(item);
        }
        _directions->setIconSize(QSize(
            mw <= 128 ? mw : 128, mh <= 128 ? mh : 128
        ));
        if (selection.haveDirection()) {
            int dir = selection.direction();
            SpriteDirection direction = animation.direction(dir);
            int w = direction.width(), h = direction.height();
            QPen pen(Qt::blue);
            for (int i = 0; i < direction.nbFrames(); i++) {
                int x = direction.x(), y = direction.y();
                int col = i % direction.nbColumns();
                int row = i / direction.nbColumns();
                x += col * w;
                y += row * h;
                _graphicsView->scene()->addRect(x, y, w, h, pen);
            }
            _directions->setCurrentRow(dir);
            _directionEditor->setEnabled(true);
            _directionPreview->setEnabled(true);
            _removeDirectionButton->setEnabled(true);
            _upDirectionButton->setEnabled(dir > 0);
            _downDirectionButton->setEnabled(
                dir + 1 < animation.countDirections()
            );
            _directionEditor->setDirection(direction);
            _directionPreview->setImage(img);
            _directionPreview->setFrameDelay(animation.frameDelay());
            _directionPreview->setFrameOnLoop(animation.frameOnLoop());
            _directionPreview->setDirection(animation.direction(dir));
        } else {
            _directionEditor->setEnabled(false);
            _directionPreview->setEnabled(false);
            _removeDirectionButton->setEnabled(false);
            _upDirectionButton->setEnabled(false);
            _downDirectionButton->setEnabled(false);
        }
        _directions->blockSignals(false);
    } else {
        _animationGroup->setEnabled(false);
        _directions->setEnabled(false);
        _directionEditor->setEnabled(false);
        _removeDirectionButton->setEnabled(false);
        _upDirectionButton->setEnabled(false);
        _downDirectionButton->setEnabled(false);
    }
}

void SpriteEditor::addAnimation (const QString &name)
{
    _animations->addItem(name, name);
    _refreshTitle();
}

void SpriteEditor::removeAnimation (const QString &name)
{
    _animations->removeItem(_animations->findData(name));
    _refreshTitle();
}

void SpriteEditor::renameAnimation (
    const QString &oldName, const QString &newName
) {
    _animations->blockSignals(true);
    int n = _animations->findData(oldName);
    _animations->setItemText(n, newName);
    _animations->setItemData(n, newName);
    _animations->blockSignals(false);
    _refreshTitle();
}

bool SpriteEditor::isSaved () const
{
    return !_sprite->canUndo();
}

void SpriteEditor::_initWidgets ()
{
    _id = new QLabel;
    _name = new QLineEdit;
    _animations = new QComboBox;
    _graphicsView = new SQCGraphicsView;
    _animationEditor = new SpriteAnimationEditor(_quest);
    _directions = new QListWidget;
    _directionEditor = new SpriteDirectionEditor;
    _addAnimationButton = new QPushButton(QIcon(":fugue/plus"), "");
    _removeAnimationButton = new QPushButton(QIcon(":fugue/minus"), "");

    _animations->setInsertPolicy(QComboBox::NoInsert);
    _addDirectionButton = new QPushButton(QIcon(":fugue/plus"), "");
    _removeDirectionButton = new QPushButton(QIcon(":fugue/minus"), "");
    _upDirectionButton = new QPushButton(QIcon(":fugue/arrow_up"), "");
    _downDirectionButton = new QPushButton(QIcon(":fugue/arrow_down"), "");

    _directionPreview = new SpriteDirectionPreview;

    _animations->setEditable(true);
    _directionEditor->setEnabled(false);
    _graphicsView->setScene(new QGraphicsScene());
    _graphicsView->setBackgroundBrush(QBrush(Qt::lightGray));
    _addAnimationButton->setMaximumSize(24, 24);
    _removeAnimationButton->setMaximumSize(24, 24);
    _removeAnimationButton->setEnabled(false);
    _addDirectionButton->setMaximumSize(24, 24);
    _removeDirectionButton->setMaximumSize(24, 24);
    _upDirectionButton->setMaximumSize(24, 24);
    _downDirectionButton->setMaximumSize(24, 24);
    _removeDirectionButton->setEnabled(false);
    _upDirectionButton->setEnabled(false);
    _downDirectionButton->setEnabled(false);
    _directionPreview->setEnabled(false);

    QFormLayout *propertiesLayout = new QFormLayout;
    propertiesLayout->addRow(tr("Id:"), _id);
    propertiesLayout->addRow(tr("Name:"), _name);
    propertiesLayout->setLabelAlignment(Qt::AlignRight);

    _animationGroup = new QGroupBox(tr("Animations"));
    QGridLayout *animationLayout = new QGridLayout;
    animationLayout->addWidget(_animations, 0, 0);
    animationLayout->addWidget(_addAnimationButton, 0, 1);
    animationLayout->addWidget(_removeAnimationButton, 0, 2);
    animationLayout->addWidget(_animationEditor, 1, 0, 1, 3);
    animationLayout->setColumnStretch(0, 1);
    _animationGroup->setLayout(animationLayout);

    QGroupBox *directionsGroup = new QGroupBox(tr("Directions"));
    QGridLayout *directionsLayout = new QGridLayout;
    directionsLayout->addWidget(_directions, 0, 0, 5, 1);
    directionsLayout->addWidget(_addDirectionButton, 0, 1);
    directionsLayout->addWidget(_removeDirectionButton, 1, 1);
    directionsLayout->addWidget(_upDirectionButton, 2, 1);
    directionsLayout->addWidget(_downDirectionButton, 3, 1);
    directionsLayout->setRowStretch(4, 1);
    directionsLayout->setColumnStretch(0, 1);
    directionsGroup->setLayout(directionsLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addLayout(propertiesLayout, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(_animationGroup, 1, 0);
    layout->addWidget(_graphicsView, 0, 1, 3, 5);
    layout->addWidget(directionsGroup, 2, 0, 2, 1);
    layout->addWidget(_directionEditor, 3, 2);
    layout->addWidget(_directionPreview, 3, 4);

    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(3, 1);
    layout->setColumnStretch(5, 1);
    layout->setRowStretch(2, 1);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(layout);

    setStatusBar(new QStatusBar());
    QToolBar *t = addToolBar("");
    _actionSave = t->addAction(QIcon(":fugue/save"), "");
    _actionUndo = t->addAction(QIcon(":fugue/undo"), "");
    _actionRedo = t->addAction(QIcon(":fugue/redo"), "");
    t->setMovable(false);

    _actionSave->setEnabled(false);
    _actionUndo->setEnabled(false);
    _actionRedo->setEnabled(false);
}

void SpriteEditor::_connects ()
{
    connect(_name, SIGNAL(editingFinished()), this, SLOT(_nameChange()));
    connect(
        _animations, SIGNAL(currentIndexChanged(int)),
        this, SLOT(_animationSelectionChange())
    );
    connect(
        _animations->lineEdit(), SIGNAL(editingFinished()),
        this, SLOT(_animationRename())
    );
    connect(
        _animationEditor, SIGNAL(animationChange(SpriteAnimation)),
        this, SLOT(_animationChange(SpriteAnimation))
    );
    connect(
        _animationEditor, SIGNAL(tilesetChange()), this, SLOT(_tilesetChange())
    );
    connect(
        _addAnimationButton, SIGNAL(clicked()),
        this, SLOT(_addAnimation())
    );
    connect(
        _removeAnimationButton, SIGNAL(clicked()),
        this, SLOT(_removeAnimation())
    );
    connect(
        _directions, SIGNAL(itemSelectionChanged()),
        this, SLOT(_directionSelectionChange())
    );
    connect(
        _directionEditor, SIGNAL(directionChange(SpriteDirection)),
        this, SLOT(_directionChange(SpriteDirection))
    );
    connect(
        _addDirectionButton, SIGNAL(clicked()), this, SLOT(_addDirection())
    );
    connect(
        _removeDirectionButton, SIGNAL(clicked()),
        this, SLOT(_removeDirection())
    );
    connect(
        _upDirectionButton, SIGNAL(clicked()), this, SLOT(_upDirection())
    );
    connect(
        _downDirectionButton, SIGNAL(clicked()), this, SLOT(_downDirection())
    );
    connect(_actionSave, SIGNAL(triggered()), this, SLOT(_save()));
    connect(_actionUndo, SIGNAL(triggered()), this, SLOT(_undo()));
    connect(_actionRedo, SIGNAL(triggered()), this, SLOT(_redo()));
}

void SpriteEditor::_refreshWidgets ()
{
    simpleRefresh(Sprite::p_name);
    _id->setText(QString("<b>") + _sprite->id() + "</b>");
    _animations->clear();
    QList<QString> list = _sprite->animationNames();
    _animationEditor->setEnabled(list.size() != 0);
    _animations->setEnabled(list.size() != 0);
    for (int i = 0; i < list.size(); ++i) {
        addAnimation(list[i]);
    }
}

void SpriteEditor::_refreshTitle ()
{
    QString title = _quest->writeDir() + " - sprite: " + _sprite->name();
    if (_sprite->canUndo()) {
        title += "*";
    }
    setWindowTitle(title);
    _actionSave->setEnabled(_sprite->canUndo());
    _actionUndo->setEnabled(_sprite->canUndo());
    _actionRedo->setEnabled(_sprite->canRedo());
}

void SpriteEditor::_swapDirection (const int &n1, const int &n2)
{
    SpriteAnimation animation = _sprite->animation(_animations->currentText());
    try {
        animation.swapDirection(n1, n2);
        _sprite->setAnimation(animation.name(), animation);
        _sprite->setSelection(SpriteSelection(animation.name(), n2));
    } catch (const SQCException &ex) {
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_nameChange ()
{
    _sprite->setName(_name->text());
}

void SpriteEditor::_animationSelectionChange ()
{
    try {
        int n = _animations->currentIndex();
        _sprite->setSelection(SpriteSelection(
            _animations->itemData(n).toString()
        ));
    } catch (const SQCException &ex) {
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_animationRename ()
{
    int n = _animations->currentIndex();
    try {
        QString oldName = _animations->itemData(n).toString();
        QString newName = _animations->currentText();
        _sprite->renameAnimation(oldName, newName);
    } catch (const SQCException &ex) {
        _animations->setCurrentIndex(n);
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_animationChange (SpriteAnimation animation)
{
    _sprite->setAnimation(animation.name(), animation);
}

void SpriteEditor::_tilesetChange ()
{
    refreshAnimation(_animationEditor->animation().name());
}

void SpriteEditor::_addAnimation ()
{
    QString dir = _quest->dataDirectory() + "sprites/";
    ImageFinder finder(this, dir);
    int r = finder.exec();
    static int n = 0;
    if (r == QDialog::Accepted) {
        QString name;
        do {
            name = QString("anim_") + QString::number(n++);
        } while (_sprite->animationExists(name));
        QString image = finder.image();
        image.replace(dir, "");
        _sprite->setAnimation(name, SpriteAnimation(name, image));
        refreshSelection(_sprite->selection());
    }
}

void SpriteEditor::_removeAnimation ()
{
    try {
        _sprite->removeAnimation(_animations->currentText());
    } catch (const SQCException &ex) {
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_directionSelectionChange ()
{
    try {
        QListWidgetItem *item = _directions->currentItem();
        int n = item->data(QListWidgetItem::UserType).toInt();
        SpriteSelection selection(_sprite->selection().animation(), n);
        _sprite->setSelection(selection);
    } catch (const SQCException &ex) {
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_directionChange (SpriteDirection direction)
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    SpriteAnimation animation = _sprite->animation(_animations->currentText());
    if (direction != animation.direction(n)) {
        animation.setDirection(n, direction);
        _sprite->setAnimation(animation.name(), animation);
    }
}

void SpriteEditor::_addDirection ()
{
    SpriteAnimation animation = _sprite->animation(_animations->currentText());
    int dir = animation.addDirection(SpriteDirection());
    _sprite->setAnimation(animation.name(), animation);
    _sprite->setSelection(SpriteSelection(animation.name(), dir));
}

void SpriteEditor::_removeDirection ()
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    SpriteAnimation animation = _sprite->animation(_animations->currentText());
    try {
        animation.removeDirection(n);
        _sprite->setAnimation(animation.name(), animation);
    } catch (const SQCException &ex) {
        statusBar()->showMessage(ex.message(), 5000);
    }
}

void SpriteEditor::_upDirection ()
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    _swapDirection(n, n - 1);
}

void SpriteEditor::_downDirection ()
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    _swapDirection(n, n + 1);
}

void SpriteEditor::_save ()
{
    emit save(this);
    _refreshTitle();
}

void SpriteEditor::_undo ()
{
    _sprite->undo();
    _refreshTitle();
}

void SpriteEditor::_redo ()
{
    _sprite->redo();
    _refreshTitle();
}
