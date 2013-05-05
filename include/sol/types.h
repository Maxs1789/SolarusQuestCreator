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
#ifndef SOL_TYPES_H
#define SOL_TYPES_H

class Quest;

class Resource;

class Map;
class Tileset;
class Music;
class Sprite;
class Sound;
class Item;
class Enemy;
class Language;

class MapEntity;
class EntityTile;
class EntityDestination;
class EntityTeletransporter;
class EntityPickable;
class EntityDestructible;
class EntityChest;
class EntityJumpSensor;
class EntityEnemy;
class EntityNPC;
class EntityBlock;
class EntityDynamicTile;
class EntitySwitch;
class EntityWall;
class EntitySensor;
class EntityCrystal;
class EntityCrystalBlock;
class EntityShopItem;
class EntityConveyorBelt;
class EntityDoor;
class EntityStairs;
class TilePattern;
class SpriteAnimation;
class SpriteDirection;
class SpriteSelection;

/**
 * @brief Type d'une Ressource.
 */
enum ResourceType
{
    MAP       = 0,       /**< Carte (Map). */
    TILESET   = 1,       /**< Tileset. */
    MUSIC     = 2,       /**< Musique (Music). */
    SPRITE    = 3,       /**< Sprite. */
    SOUND     = 4,       /**< Son (Sound). */
    ITEM      = 5,       /**< Objet (Item). */
    ENEMY     = 6,       /**< Enemis (Enemy). */
    LANGUAGE  = 7,       /**< Langue (Language). */
    N_RESOURCE_TYPE = 8  /**< Nombre de type. */
};

/**
 * @brief Couche d'une entitée de Carte (Map).
 *
 * @see TilePattern, MapEntity
 */
enum Layer
{
    LOW           = 0,  /**< Basse. */
    INTERMEDIATE  = 1,  /**< Intérmédiaire. */
    HIGH          = 2   /**< Haute. */
};

/**
 * @brief Type d'obstacle que peut avoir un Tile.
 *
 * @see TilePattern, EntityTile, EntityDynamicTile
 */
enum Ground
{
    TRAVERSABLE,         /**< Traversable. */
    WALL,                /**< Mur. */
    WALL_TOP_RIGHT,      /**< Mur Nord-Est. */
    WALL_TOP_LEFT,       /**< Mur Nord-Ouest. */
    WALL_BOTTOM_LEFT,    /**< Mur Sud-Ouest. */
    WALL_BOTTOM_RIGHT,   /**< Mur Sud-Est. */
    EMPTY,               /**< Vide. */
    WATER_TOP_RIGHT,     /**< Mur Nord-Est dans l'eau profonde. */
    WATER_TOP_LEFT,      /**< Mur Nord-Ouest dans l'eau profonde. */
    WATER_BOTTOM_LEFT,   /**< Mur Sud-Ouest dans l'eau profonde. */
    WATER_BOTTOM_RIGHT,  /**< Mur Sud-Est dans l'eau profonde. */
    DEEP_WATER,          /**< Eau profonde. */
    SHALLOW_WATER,       /**< Eau peu profonde. */
    HOLE,                /**< Trou. */
    LADDER,              /**< Échelle. */
    PRICKLES,            /**< Piques. */
    LAVA                 /**< Lave. */
};
/**
 * @brief Type de défilement d'un Tile.
 *
 * @see TilePattern, EntityTile, EntityDynamicTile
 */
enum Scrolling
{
    NO_SCROLLING,  /**< Aucun défilement. */
    SELF,          /**< Défilement sur sois-même. */
    PARALLAX       /**< Défilement caméra. */
};

/**
 * @brief Couleur de type rgb.
 */
struct Color
{
    char red;    /**< Niveau de rouge de la couleur. */
    char green;  /**< Niveau de vert de la couleur. */
    char blue;   /**< Niveau de bleu de la couleur. */

    /**
     * @brief Opérateur de comparaison par différence.
     *
     * Utilisé par le Tileset.
     *
     * @param other La couleur à comparer
     *
     * @return `true` si la couleur est différente, `false` sinon.
     */
    bool operator != (const Color &other)
    {
        return other.red != red || other.green != green || other.blue != blue;
    }
};

struct Rect
{
    int x;
    int y;
    int width;
    int height;
};

#endif
