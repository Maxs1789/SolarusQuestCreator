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
#ifndef NEW_RESOURCE_DIALOG_H
#define NEW_RESOURCE_DIALOG_H

#include <QDialog>
#include "sol/types.h"

class QLineEdit;
class QDialogButtonBox;

/**
 * @brief Dialogue de création d'un ressource.
 */
class NewResourceDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur du dialogue.
     *
     * @param parent Le widget parent
     */
    NewResourceDialog (QWidget *parent);
    /**
     * @brief Donne le nom de la ressource à créer.
     *
     * @return Le nom de la ressource à créer.
     */
    QString name () const;
    /**
     * @brief Donne l'identifiant de la ressource à créer.
     *
     * @return L'identifiant de la ressource à créer.
     */
    QString id () const;
    /**
     * @brief Change la liste des identifiants du type de la ressource à créer.
     *
     * Permet au dialogue d'empècher l'utilisateur de donner un identifiant déjà
     * utilisé.
     *
     * @param resourceIds La liste des identifiants
     */
    void setResourceIds (QList<QString> resourceIds);

private:
    QLineEdit *_name;
    QLineEdit *_id;
    QDialogButtonBox *_buttonBox;
    QList<QString> _ids;
    bool _clean;

    void _initWidgets ();

private slots:
    void _nameChange (QString name);
    void _idChange (QString id);
};

#endif
