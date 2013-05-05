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
#include "util/FileTools.h"
#include <QFile>
#include <QDir>

QString FileTools::absolutePath(QString path)
{
    QFileInfo info(path);
    if (info.isDir()) {
        info.setFile(path + "/");
    }
    return info.absoluteFilePath();
}

bool FileTools::fileExists (QString filename)
{
    QFile file(filename);
    return file.exists();
}

bool FileTools::directoryExists (QString directory)
{
    QDir dir(directory);
    return dir.exists();
}

void FileTools::makeDirectory (QString directory) throw(IOException)
{
    if (directoryExists(directory)) {
        throw IOException(IOException::DIR_EXISTS, directory);
    }
    QDir dir;
    if (!dir.mkdir(directory)) {
        throw IOException(IOException::DIR_N_WRITE, directory);
    }
}

void FileTools::copy (QString source, QString destination) throw(IOException)
{
    QFile file(source);
    if (!file.exists()) {
        throw IOException(IOException::FILE_N_EXISTS, source);
    }
    if (!file.copy(destination)) {
        throw IOException(IOException::FILE_N_WRITE, destination);
    }
}
/*
const char *FileTools::readFile (QString filename) throw(IOException)
{
    QFile file(filename);
    if (!file.exists()) {
        throw IOException(IOException::FILE_N_EXISTS, filename);
    }
    if (!file.open(QIODevice::ReadOnly)) {
        throw IOException(IOException::FILE_N_READ, filename);
    }
    QByteArray array = file.readAll();
    file.close();
    char *data = new char[array.size() + 1];
    memcpy(data, array.data(), array.size()+1);
    return data;
}

void FileTools::saveFile (QString filename, const char *data) throw(IOException)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw IOException(IOException::FILE_N_WRITE, filename);
    }
    file.write(data);
    file.close();
}
*/
