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
#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "sol/types.h"
#include "exception/SQCException.h"

/**
 * @brief Classe abstraite d'un éditeur de ressource.
 */
class Editor : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de l'éditeur.
     *
     * @param questDir Le dossier de la quete
     * @param type     Le type de la ressource à éditer
     * @param id       L'identifiant de la ressource
     */
    Editor (QString questDir, ResourceType type, QString id);
    /**
     * @brief Donne le dossier de la quete de la ressource éditée.
     *
     * @return Le dossier de la quete.
     */
    QString questDir () const;
    /**
     * @brief Donne le type de la ressource éditée.
     *
     * @return Le type de la ressource.
     */
    ResourceType type () const;
    /**
     * @brief Donne l'identifiant de la ressource éditée.
     *
     * @return L'identifiant de la ressource éditée.
     */
    QString id () const;
    /**
     * @brief Vérifie que la ressource est à l'état de sauvegarde.
     *
     * @return `true` si la ressource est à l'état de sauvegarde, `false` sinon.
     */
    virtual bool isSaved () const = 0;
    /**
     * @brief Sauvegarde la ressource.
     *
     * @param dataDirectory Le dossier de travail de la quete dans lequel
     *                       sauvegarder la ressource.
     *
     * @throw SQCException Si la ressource ne peut etre sauvegardée.
     */
    virtual void save (QString dataDirectory) throw(SQCException) = 0;

signals:
    /**
     * @brief Emit lorsque l'on clique sur le bouton de sauvegarde.
     *
     * L'éditeur ne sauvegarde pas lui meme la ressource, ce fonctionnalité est
     * prise en charge par la fenetre principale.
     */
    void onSave (Editor *);
    /**
     * @brief Emit lorsque l'éditeur se ferme.
     */
    void onClose (Editor *);

protected:
    void closeEvent (QCloseEvent *event);

private:
    QString _questDir;
    ResourceType _type;
    QString _id;
};

#endif
