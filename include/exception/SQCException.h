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
#ifndef SQC_EXCEPTION_H
#define SQC_EXCEPTION_H

#include <exception>
#include <QString>

using namespace std;

/**
 * @brief Exception générique des modèles.
 */
class SQCException : public exception
{
public:
    /**
     * @brief Constructeur de l'exception.
     *
     * @param message Message de l'exception
     */
    SQCException (QString message = "") throw() :
        _message(message)
    {}
    /**
     * @brief Destructeur de l'exception.
     */
    ~SQCException () throw()
    {}
    /**
     * @brief Donne le message de l'exception.
     *
     * @return Le message de l'exception.
     */
    QString message () const throw()
    {
        return _message;
    }
    /**
     * @brief Retourne le message de l'exception.
     *
     * @return Le message de l'exception.
     */
    const char *what () const throw()
    {
        return _message.toStdString().c_str();
    }

protected:
    /**
     * @brief Modifie le message de l'exception.
     *
     * @param message Le nouveau message
     */
    void setMessage (QString message) throw()
    {
        _message = message;
    }

private:
    QString _message;
};

#endif
