#ifndef _TERRAIN_H_
#define _TERRAIN_H_

// General terrain types
#define TERRAIN_WILDERNESS   128
#define TERRAIN_WATER        256
#define TERRAIN_INDOOR       512
#define TERRAIN_POPULATED   1024
#define TERRAIN_OUTDOOR     2048
#define TERRAIN_CLUTTERED     4096

// Wilderness terrain
#define TERRAIN_PLAIN        TERRAIN_WILDERNESS + 1
#define TERRAIN_MOUNTAIN     TERRAIN_WILDERNESS + 2
#define TERRAIN_FOREST       TERRAIN_WILDERNESS + 3
#define TERRAIN_SWAMP        TERRAIN_WILDERNESS + 4
#define TERRAIN_DESERT       TERRAIN_WILDERNESS + 5
#define TERRAIN_JUNGLE       TERRAIN_WILDERNESS + 6
#define TERRAIN_BUSH         TERRAIN_WILDERNESS + 7
#define TERRAIN_HILL         TERRAIN_WILDERNESS + 8
#define TERRAIN_CLIFF        TERRAIN_WILDERNESS + 9
#define TERRAIN_THICKET      TERRAIN_WILDERNESS + 10
#define TERRAIN_RIVBANK      TERRAIN_WILDERNESS + 11
#define TERRAIN_COAST        TERRAIN_WILDERNESS + 12
#define TERRAIN_WETLAND      TERRAIN_WILDERNESS + 13
#define TERRAIN_GLACIER      TERRAIN_WILDERNESS + 14
#define TERRAIN_MOOR         TERRAIN_WILDERNESS + 15
#define TERRAIN_BADLANDS     TERRAIN_WILDERNESS + 16
#define TERRAIN_LAKESHORE    TERRAIN_WILDERNESS + 17
#define TERRAIN_BEACH        TERRAIN_WILDERNESS + 18

// Water terrain
#define TERRAIN_SEA          TERRAIN_WATER + 1
#define TERRAIN_RIVER        TERRAIN_WATER + 2
#define TERRAIN_LAKE         TERRAIN_WATER + 3
#define TERRAIN_POND         TERRAIN_WATER + 4
#define TERRAIN_STREAM       TERRAIN_WATER + 5
#define TERRAIN_WATERFALL    TERRAIN_WATER + 6

// Indoor terrain
#define TERRAIN_INSHIP       TERRAIN_INDOOR + 1
#define TERRAIN_NATCAVE      TERRAIN_INDOOR + 2
#define TERRAIN_CRYPT        TERRAIN_INDOOR + 3
#define TERRAIN_HOUSE        TERRAIN_INDOOR + 4
#define TERRAIN_HALL         TERRAIN_INDOOR + 5
#define TERRAIN_MINE         TERRAIN_INDOOR + 6
#define TERRAIN_SEWER        TERRAIN_INDOOR + 7
#define TERRAIN_CARVEDCAVE   TERRAIN_INDOOR + 8
#define TERRAIN_TUNNEL       TERRAIN_INDOOR + 9
#define TERRAIN_INRUINS      TERRAIN_INDOOR + 10

// Populated terrain
#define TERRAIN_VILLAGE      TERRAIN_POPULATED + 1
#define TERRAIN_CITY         TERRAIN_POPULATED + 2
#define TERRAIN_STREET       TERRAIN_POPULATED + 3
#define TERRAIN_ALLEY        TERRAIN_POPULATED + 4
#define TERRAIN_FORTRESS     TERRAIN_POPULATED + 5

// Outdoor, not usually wilderness terrain
#define TERRAIN_PATH         TERRAIN_OUTDOOR + 1
#define TERRAIN_ROAD         TERRAIN_OUTDOOR + 2
#define TERRAIN_BRIDGE       TERRAIN_OUTDOOR + 3
#define TERRAIN_OUTRUINS     TERRAIN_OUTDOOR + 4
#define TERRAIN_GARDEN       TERRAIN_OUTDOOR + 5
#define TERRAIN_FIELD        TERRAIN_OUTDOOR + 6
#define TERRAIN_PIER         TERRAIN_OUTDOOR + 7

// Cluttered terrain
#define TERRAIN_LITTERED     TERRAIN_CLUTTERED + 1
#define TERRAIN_SNOW         TERRAIN_CLUTTERED + 2
#define TERRAIN_ICE          TERRAIN_CLUTTERED + 3
#define TERRAIN_MUD          TERRAIN_CLUTTERED + 4
#define TERRAIN_FOG          TERRAIN_CLUTTERED + 5
#define TERRAIN_LEAFLITTER   TERRAIN_CLUTTERED + 6
#define TERRAIN_LAVA         TERRAIN_CLUTTERED + 7
#define TERRAIN_WELL         TERRAIN_CLUTTERED + 8

#define TERRAIN_MAP ([ \
    "plain" : TERRAIN_PLAIN, \
    "mountain" : TERRAIN_MOUNTAIN, \
    "forest" : TERRAIN_FOREST, \
    "swamp" : TERRAIN_SWAMP, \
    "desert" : TERRAIN_DESERT, \
    "jungle" : TERRAIN_JUNGLE, \
    "bush" : TERRAIN_BUSH, \
    "hill" : TERRAIN_HILL, \
    "cliff" : TERRAIN_CLIFF, \
    "thicket" : TERRAIN_THICKET, \
    "riverbank" : TERRAIN_RIVBANK, \
    "coast" : TERRAIN_COAST, \
    "wetland" : TERRAIN_WETLAND, \
    "glacier" : TERRAIN_GLACIER, \
    "moor" : TERRAIN_MOOR, \
    "badlands" : TERRAIN_BADLANDS, \
    "lakeshore" : TERRAIN_LAKESHORE, \
    "beach" : TERRAIN_BEACH, \
    "sea" : TERRAIN_SEA, \
    "river" : TERRAIN_RIVER, \
    "lake" : TERRAIN_LAKE, \
    "pond" : TERRAIN_POND, \
    "stream" : TERRAIN_STREAM, \
    "waterfall" : TERRAIN_WATERFALL, \
    "in ship" : TERRAIN_INSHIP, \
    "natural cave" : TERRAIN_NATCAVE, \
    "crypt" : TERRAIN_CRYPT, \
    "house" : TERRAIN_HOUSE, \
    "hall" : TERRAIN_HALL, \
    "mine" : TERRAIN_MINE, \
    "sewer" : TERRAIN_SEWER, \
    "constructed cave" : TERRAIN_CARVEDCAVE, \
    "tunnel" : TERRAIN_TUNNEL, \
    "inside ruins" : TERRAIN_INRUINS, \
    "littered" : TERRAIN_LITTERED, \
    "snow" : TERRAIN_SNOW, \
    "ice" : TERRAIN_ICE, \
    "mud" : TERRAIN_MUD, \
    "fog" : TERRAIN_FOG, \
    "leaf litter" : TERRAIN_LEAFLITTER, \
    "lava" : TERRAIN_LAVA, \
    "water well" : TERRAIN_WELL, \
    "village" : TERRAIN_VILLAGE, \
    "city" : TERRAIN_CITY, \
    "street" : TERRAIN_STREET, \
    "alley" : TERRAIN_ALLEY, \
    "fortress" : TERRAIN_FORTRESS, \
    "outside ruins" : TERRAIN_OUTRUINS, \
    "path" : TERRAIN_PATH, \
    "road" : TERRAIN_ROAD, \
    "bridge" : TERRAIN_BRIDGE, \
    "garden" : TERRAIN_GARDEN, \
    "field" : TERRAIN_FIELD, \
    "pier" : TERRAIN_PIER ])

#endif

