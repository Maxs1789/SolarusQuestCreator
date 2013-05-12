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
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include "gui/dialog/SpriteEditorOptionDialog.h"
#include "gui/option/SpriteGraphicsViewOption.h"
#include "gui/option/SpritePreviewOption.h"

SpriteEditorOptionDialog::SpriteEditorOptionDialog (
    SpriteGraphicsView *mainView, SpriteDirectionGraphicsView *directionPreview
) :
    _mainOption(new SpriteGraphicsViewOption(mainView)),
    _previewOption(new SpritePreviewOption(directionPreview))
{
    setWindowTitle(tr("Sprite editor options"));
    _buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    QGroupBox *mainGroup = new QGroupBox(tr("Main graphics view"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_mainOption);
    mainGroup->setLayout(mainLayout);

    QGroupBox *previewGroup = new QGroupBox(tr("Direction previewer"));
    QVBoxLayout *previewLayout = new QVBoxLayout;
    previewLayout->addWidget(_previewOption);
    previewGroup->setLayout(previewLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mainGroup);
    layout->addWidget(previewGroup);
    layout->addWidget(_buttonBox);
    setLayout(layout);

    connect(_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void SpriteEditorOptionDialog::setSettings ()
{
    _mainOption->setSettings();
    _previewOption->setSettings();
}
