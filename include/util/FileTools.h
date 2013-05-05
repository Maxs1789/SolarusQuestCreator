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
#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H

#include "exception/IOException.h"

/**
 * @brief Classe utilitaire pour la manipulation des fichiers.
 */
class FileTools
{
public:
    /**
     * @brief Retourne le chemin absolu d'un fichier.
     *
     * @param path Le chemin du fichier
     *
     * @return Le chemin absolu de ce fichier.
     */
    static QString absolutePath (QString path);
    /**
     * @brief Vérifie qu'un fichier existe bien.
     *
     * @param filename Le nom du fichier à vérifier
     *
     * @return `true` si le fichier existe, `false` sinon.
     */
    static bool fileExists (QString filename);
    /**
     * @brief Vérifie qu'un dossier existe bien.
     *
     * @param directory Le nom du dossier à vérifier
     *
     * @return `true` si le dossier existe, `false` sinon.
     */
    static bool directoryExists (QString directory);
    /**
     * @brief Crée un nouveau dossier.
     *
     * @param directory Le nom du dossier à créer
     *
     * @throw IOException Si le fichier existe déjà ou ne peut être crée.
     */
    static void makeDirectory (QString directory) throw(IOException);
    /**
     * @brief Copie un fichier.
     *
     * @param source      Le nom du fichier à copier
     * @param destination Le nom de fichier à créer
     *
     * @throw IOException Si la source n'existe pas ou que la destination ne
     * peut être crée.
     */
    static void copy (QString source, QString destination) throw(IOException);
};

#endif
