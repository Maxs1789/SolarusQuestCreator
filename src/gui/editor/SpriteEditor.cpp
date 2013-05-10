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
#include "gui/widget/SpriteGraphicsView.h"
#include "gui/editor/SpriteEditor.h"
#include "gui/editor/SpriteAnimationEditor.h"
#include "gui/editor/SpriteDirectionEditor.h"
#include "sol/Quest.h"
#include "sol/SpriteAnimation.h"
#include "gui/dialog/ImageFinder.h"
#include "gui/widget/SpriteDirectionPreview.h"
#include "gui/widget/ColorButton.h"

SpriteEditor::SpriteEditor (Quest *quest, const Sprite &sprite) :
    Editor(quest->directory(), SPRITE, sprite.id()),
    _quest(quest),
    _sprite(new Sprite("")),
    _animCount(0)
{
    *_sprite = sprite;
    _sprite->attach(this);
    _initWidgets();
    _firstRefresh();
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
    bool empty = selection.isEmpty();
    if (!empty) {
        int n = _animations->findText(selection.animation());
        _animations->blockSignals(true);
        _animations->setCurrentIndex(n);
        refreshAnimation(selection.animation());
        _animations->blockSignals(false);
    }
    _removeAnimationButton->setEnabled(!empty);
    _animationEditor->setEnabled(!empty);
    _animations->setEnabled(!empty);
    _graphicsView->setEnabled(!empty);
    _directionGroup->setEnabled(!empty);
}

void SpriteEditor::refreshAnimation (const QString &name)
{
    SpriteAnimation animation = _sprite->animation(name);
    SpriteSelection selection = _sprite->selection();
    bool enableAnim = !selection.isEmpty() && selection.animation() == name;
    if (
        enableAnim && !selection.haveDirection() &&
        !selection.isNewDirection() && animation.countDirections() &&
        !_addDirectionButton->isChecked()
    ) {
        selection = SpriteSelection(name, 0);
    }
    bool enableDir = enableAnim && selection.haveDirection();

    _setCurrentImage(animation.image());

    _graphicsView->setEnabled(enableAnim);
    _directions->setEnabled(enableAnim);
    _directionEditor->setEnabled(enableDir);
    _directionPreview->setEnabled(enableDir);
    _removeDirectionButton->setEnabled(enableDir);
    _upDirectionButton->setEnabled(enableDir);
    _downDirectionButton->setEnabled(enableDir);

    if (enableAnim) {
        _animationEditor->setAnimation(animation);
        _graphicsView->setSelection(animation, selection);
        _refreshDirections(animation.allDirections());
        if (enableDir) {
            int dir = selection.direction();
            SpriteDirection direction = animation.direction(dir);
            _refreshDirectionEditor(dir, direction);
            _refreshDirectionPreview(animation, direction);
        }
    }
    _refreshTitle();
}

void SpriteEditor::addAnimation (const QString &name)
{
    _animations->blockSignals(true);
    _animations->addItem(name, name);
    _animations->blockSignals(false);
    refreshSelection(_sprite->selection());
    _refreshTitle();
}

void SpriteEditor::removeAnimation (const QString &name)
{
    int n = _animations->findData(name);
    if (n >= 0) {
        if (_animations->count() > 1) {
            _animations->removeItem(n);
        } else {
            _animations->blockSignals(true);
            _animations->removeItem(n);
            _animations->blockSignals(false);
            refreshSelection(_sprite->selection());
        }
    }
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
    _graphicsView = new SpriteGraphicsView;
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
    _animations->setEnabled(false);
    _graphicsView->setMakeSelection(true);
    _addAnimationButton->setMaximumSize(24, 24);
    _removeAnimationButton->setMaximumSize(24, 24);
    _removeAnimationButton->setEnabled(false);
    _addDirectionButton->setMaximumSize(24, 24);
    _addDirectionButton->setCheckable(true);
    _removeDirectionButton->setMaximumSize(24, 24);
    _upDirectionButton->setMaximumSize(24, 24);
    _downDirectionButton->setMaximumSize(24, 24);
    _removeDirectionButton->setEnabled(false);
    _upDirectionButton->setEnabled(false);
    _downDirectionButton->setEnabled(false);
    _directionPreview->setEnabled(false);
    _directions->setIconSize(QSize(128, 128));

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

    _directionGroup = new QGroupBox(tr("Directions"));
    QGridLayout *directionsLayout = new QGridLayout;
    directionsLayout->addWidget(_directions, 0, 0, 5, 1);
    directionsLayout->addWidget(_addDirectionButton, 0, 1);
    directionsLayout->addWidget(_removeDirectionButton, 1, 1);
    directionsLayout->addWidget(_upDirectionButton, 2, 1);
    directionsLayout->addWidget(_downDirectionButton, 3, 1);
    directionsLayout->setRowStretch(4, 1);
    directionsLayout->setColumnStretch(0, 1);
    _directionGroup->setLayout(directionsLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addLayout(propertiesLayout, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(_animationGroup, 1, 0);
    layout->addWidget(_graphicsView, 0, 1, 3, 5);
    layout->addWidget(_directionGroup, 2, 0, 2, 1);
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
    _colorButton = new ColorButton(Qt::white);
    t->addWidget(_colorButton);
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
        _graphicsView, SIGNAL(newSelection(Rect)),
        this, SLOT(_directionNewSelection(Rect))
    );
    connect(
        _directionEditor, SIGNAL(directionChange(SpriteDirection)),
        this, SLOT(_directionChange(SpriteDirection))
    );
    connect(
        _animationEditor, SIGNAL(directAnimationChange(SpriteAnimation)),
        this, SLOT(_directAnimationChange(SpriteAnimation))
    );
    connect(
        _directionEditor, SIGNAL(directDirectionChange(SpriteDirection)),
        this, SLOT(_directDirectionChange(SpriteDirection))
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
    connect(
        _colorButton, SIGNAL(colorChange(QColor)),
        _graphicsView, SLOT(setSelectionColor(QColor))
    );
}

void SpriteEditor::_firstRefresh ()
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
    if (!_sprite->isSaved()) {
        title += "*";
    }
    setWindowTitle(title);
    _actionSave->setEnabled(!_sprite->isSaved());
    _actionUndo->setEnabled(_sprite->canUndo());
    _actionRedo->setEnabled(_sprite->canRedo());
}

void SpriteEditor::_refreshDirections (const QList<SpriteDirection> &directions)
{
    _directions->blockSignals(true);
    _directions->clear();
    int n = directions.size();
    for (int i = 0; i < n; i++) {
        SpriteDirection direction = directions[i];
        QPixmap pix = _currentImage.copy(
            direction.x(), direction.y(),
            direction.width(), direction.height()
        );
        QString str = QString::number(i) + _directionName(i, n);
        QListWidgetItem *item = new QListWidgetItem(QIcon(pix), str);
        item->setData(QListWidgetItem::UserType, i);
        _directions->addItem(item);
    }
    _directions->blockSignals(false);
}

QString SpriteEditor::_directionName (const int &dir, const int &n)
{
    QString r = tr("right"), u = tr("up"), l = tr("left"), d = tr("down");
    QString ur = tr("up right"), ul = tr("up left"), dl = tr("down left");
    QString dr = tr("down right"), str;
    if (n >= 4) {
        bool gr = n >= 8;
        if (dir < 4 || (gr && dir < 8)) {
            str = " - ";
        }
        if (dir == 0) {
            str += r;
        } else if (dir < 4) {
            switch (dir) {
            case 1: str += gr ? ur : u; break;
            case 2: str += gr ? u : l; break;
            case 3: str += gr ? ul : d; break;
            }
        } else if (gr) {
            switch (dir) {
            case 4: str += l; break;
            case 5: str += dl; break;
            case 6: str += d; break;
            case 7: str += dr; break;
            }
        }
    }
    return str;
}

void SpriteEditor::_setCurrentImage (QString imagePath)
{
    if (imagePath == "tileset") {
        imagePath = _quest->dataDirectory() + "tilesets/";
        imagePath += _animationEditor->tileset() + ".entities.png";
    } else {
        imagePath = _quest->dataDirectory() + "sprites/" + imagePath;
    }
    _currentImage.load(imagePath);
    _graphicsView->setImage(_currentImage);
}

void SpriteEditor::_refreshDirectionEditor (
    const int &n, const SpriteDirection &direction
) {
    _directions->blockSignals(true);
    _directions->setCurrentRow(n);
    _directions->blockSignals(false);
    _upDirectionButton->setEnabled(n > 0);
    _downDirectionButton->setEnabled(n + 1 < _directions->count());
    _directionEditor->setDirection(direction);
}

void SpriteEditor::_refreshDirectionPreview (
    const SpriteAnimation &animation, const SpriteDirection &direction
) {
    _directionPreview->setImage(_currentImage);
    _directionPreview->setFrameDelay(animation.frameDelay());
    _directionPreview->setFrameOnLoop(animation.frameOnLoop());
    _directionPreview->setDirection(direction);
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

void SpriteEditor::_addDirection (Rect selection)
{
    try {
        SpriteAnimation animation;
        animation= _sprite->animation(_animations->currentText());
        int dir = animation.addDirection(SpriteDirection(selection));
        _sprite->setAnimation(animation.name(), animation);
        _sprite->setSelection(SpriteSelection(animation.name(), dir));
        _addDirectionButton->setChecked(false);
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
    if (r == QDialog::Accepted) {
        QString name;
        do {
            name = QString("anim_") + QString::number(_animCount++);
        } while (_sprite->animationExists(name));
        QString image = finder.image();
        image.replace(dir, "");
        _sprite->setAnimation(name, SpriteAnimation(name, image));
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

void SpriteEditor::_directionNewSelection (Rect selection)
{
    if (_addDirectionButton->isChecked()) {
        _addDirection(selection);
    } else {
        try {
            SpriteSelection sel(_sprite->selection().animation(), selection);
            _sprite->setSelection(sel);
        } catch (const SQCException &ex) {
            statusBar()->showMessage(ex.message(), 5000);
        }
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

void SpriteEditor::_directAnimationChange (SpriteAnimation animation)
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    SpriteDirection direction = animation.direction(n);
    _refreshDirectionPreview(animation, direction);
}

void SpriteEditor::_directDirectionChange (SpriteDirection direction)
{
    int n = _directions->currentItem()->data(QListWidgetItem::UserType).toInt();
    SpriteSelection selection(_sprite->selection().animation(), n);
    SpriteAnimation animation = _sprite->animation(selection.animation());
    animation.setDirection(selection.direction(), direction);
    _refreshDirectionPreview(animation, direction);
    _graphicsView->setSelection(animation, selection);
}

void SpriteEditor::_addDirection ()
{
    if (_addDirectionButton->isChecked()) {
        SpriteSelection selection = _sprite->selection();
        if (selection.isNewDirection()) {
            _addDirection(selection.newDirection());
        } else {
            try {
                selection = SpriteSelection(_sprite->selection().animation());
                _sprite->setSelection(selection);
            } catch (const SQCException &ex) {
                statusBar()->showMessage(ex.message(), 5000);
            }
        }
    }
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
