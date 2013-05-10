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
#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include "Action.h"

/**
 * @brief Classe abstraite de modèle.
 *
 * Cette classe à un paramètre template représentant le type de vues que
 * manipule le modèle. Il doit hériter de la classe View (ou offrir la même
 * méthode). Elle permet au modèle en manipulant des actions, de fournir une
 * notification spécifique à ses vues.
 *
 * @see Action, View
 */
template<typename type_View>
class Model
{
public:
    /**
     * @brief Destructeur de modèle.
     */
    ~Model ()
    {
        for (int i = 0; i < _actions.size(); i++) {
            delete _actions[i];
        }
    }
    /**
     * @brief Attache une vue au modèle.
     *
     * @param view La vue à attacher au modèle
     */
    void attach (type_View *view)
    {
        if (!_views.contains(view)) {
            _views.push_back(view);
        }
    }
    /**
     * @brief Détache une vue du modèle.
     *
     * @param view La vue à détacher du modèle
     */
    void detach (type_View *view)
    {
        int i = _views.indexOf(view);
        if (i >= 0) {
            _views.removeAt(i);
        }
    }
    /**
     * @brief Vérifie que le modèle peut annuler une action précèdement
     *         effectuée.
     *
     * @return `true` si le modèle peut annuler l'action, `false` sinon.
     */
    bool canUndo () const
    {
        return _currentAction != _actions.begin();
    }
    /**
     * @brief Vérifie que le modèle peut refaire la dernière action annulée.
     *
     * @return `true` si le modèle peut refaire l'action, `false` sinon.
     */
    bool canRedo () const
    {
        return _currentAction != _actions.end();
    }
    /**
     * @brief Annule la dernière action effectuée.
     */
    void undo ()
    {
        if (canUndo()) {
            _currentAction--;
            (*_currentAction)->reverse();
            _notifyAction(*_currentAction);
        }
    }
    /**
     * @brief Réexécute la dernière action annulée.
     */
    void redo ()
    {
        if (canRedo()) {
            Action *action = *_currentAction;
            action->execute();
            _currentAction++;
            _notifyAction(action);
        }
    }
    /**
     * @brief Supprime toute les actions.
     */
    void clearActions ()
    {
        for (int i = 0; i < _actions.size(); i++) {
            delete _actions[i];
        }
        _actions.clear();
        _currentAction = _actions.end();
    }

protected:
    /**
     * @brief Constructeur de modèle.
     */
    Model () :
        _saveReference(0)
    {
        _currentAction = _actions.end();
    }
    /**
     * @brief Exécute une action.
     *
     * Lorsqu'une action est exécutée, annulée ou réexécutée, les vues reçoivent
     * une notification. Si l'action est de type **BASIC_ACTION**, un appel de
     * la méthode `void simpleRefresh (string)` des vues sera fait avec comme
     * paramètre la valeur de retour de la méthode `string message ()` de
     * l'action en question. Dans le cas contraire, la méthode
     * Model::onActionNotify sera appelée pour chacune des vues.
     *
     * Ainsi il est possible de donner un type spécifique aux actions et de
     * notifier les vues de la manière la plus appropriée.
     *
     * @param action L'action à exécuter.
     *
     * @see Action, View
     */
    void doAction (Action *action)
    {
        if (canRedo()) {
            QList<Action *>::iterator it = _currentAction;
            for (; it != _actions.end(); it++) {
                delete *it;
            }
            _actions.erase(_currentAction, _actions.end());
        }
        _actions.push_back(action);
        _currentAction = _actions.end();
        action->execute();
        _notifyAction(action);
    }
    /**
     * @brief Permet d'effectuer une notification personnalisé sur les vues du
     *         modèle.
     *
     * Cette méthode appelera pour chaque vue Model::onUserNotify.
     *
     * @param userType Le type de notification.
     */
    void userNotify (int userType)
    {
        for (int i = 0; i < _views.size(); i++) {
            onUserNotify(userType, _views[i]);
        }
    }
    /**
     * @brief Appelée pour chaque vue lorsqu'une action non basique est
     *         exécutée.
     *
     * @param action L'action exécutée.
     * @param view   La vue à notifier.
     *
     * @see doAction
     */
    virtual void onActionNotify (Action *action, type_View *view) = 0;
    /**
     * @brief Appelée pour chaque vue lors de l'appel de la méthode
     *         Model::userNotify.
     *
     * @param userType Le type de notification à faire.
     * @param view     La vue à notifier.
     */
    virtual void onUserNotify (int userType, type_View *view) = 0;
    /**
     * @brief Vérifie la référence de sauvegarde du modèle.
     *
     * @return `true` si le modèle est à l'état de sauvegarde, `false` sinon.
     */
    bool checkSaveReference () const
    {
        if (_saveReference == 0) {
            return !canUndo();
        }
        return _saveReference == *(_currentAction - 1);
    }
    /**
     * @brief Fait pointer la référence de sauvegarde sur l'état courant.
     */
    void resetSaveReference ()
    {
        _saveReference = *(_currentAction - 1);
    }

private:
    QList<type_View *> _views;
    QList<Action *> _actions;
    QList<Action *>::iterator _currentAction;
    Action *_saveReference;

    void _notifyAction (Action *action)
    {
        for (int i = 0; i < _views.size(); i++) {
            if (action->isBasicAction()) {
                _views[i]->simpleRefresh(action->message());
            } else {
                onActionNotify(action, _views[i]);
            }
        }
    }
};

#endif
