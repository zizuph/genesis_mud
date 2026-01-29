#include "../defs.h"

#ifndef __RHOVANION_MIRKWOOD_DEFINES__
#define __RHOVANION_MIRKWOOD_DEFINES__


#define MIRKWOOD_DIR           		(RHOVANION_DIR + "mirkwood/")
#define MIRKWOOD_STD_DIR        	(MIRKWOOD_DIR + "std/")
#define MIRKWOOD_LIB_DIR        	(MIRKWOOD_DIR + "lib/")
#define MIRKWOOD_OLDROAD_DIR    	(MIRKWOOD_DIR + "oldroad/")
#define MIRKWOOD_OBJ_DIR        	(MIRKWOOD_DIR + "obj/")
#define MIRKWOOD_CENTRAL_FOREST_DIR (MIRKWOOD_DIR + "central_forest/")
#define MIRKWOOD_NORTH_FOREST_DIR	(MIRKWOOD_DIR + "north_forest/")
#define MIRKWOOD_SOUTH_FOREST_DIR	(MIRKWOOD_DIR + "south_forest/")
#define MIRKWOOD_ELFPATH_DIR        (MIRKWOOD_DIR + "elfpath/")
#define MIRKWOOD_SPIDER_DIR         (MIRKWOOD_DIR + "spiders/")
#define WOODSMEN_DIR                (MIRKWOOD_DIR + "woodsmen/")
#define GOBLINS_DIR                 (MIRKWOOD_DIR + "goblins/")

#define MIRKWOOD_MASTER             (MIRKWOOD_DIR + "master")
#define MIRKWOOD_SPIDER_FOLLOW_SHADOW (MIRKWOOD_SPIDER_DIR + "follow")

#define SPIDER_LIMIT_NESTS      "nests"
#define SPIDER_LIMIT_HOSTS      "hosts"

#define LIGHT_NIGHT             0
#define LIGHT_DUSKDAWN          1
#define LIGHT_MIDDAY            2
#define LIGHT_BRIGHT            3

#define LIGHT_ALL               ({ LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT })

#define LOCATION_WEST_EDGE      1
#define LOCATION_WEST_PART      2
#define LOCATION_MIDDLE         3
#define LOCATION_EAST_PART      4
#define LOCATION_EAST_EDGE      5

#define WARNING_ROAD            1
#define WARNING_FOREST          2

#define MIRKWOOD_SPIDER_NEST_ID "_mirkwood_spider_nest"
#define MIRKWOOD_SPIDER_ID      "_mirkwood_spider"

#define TREASURE_MINOR_CONSUME  "minor consume"
#define TREASURE_MAJOR_CONSUME  "major consume"
#define TREASURE_MINOR_ITEM1    "minor item 1"
#define TREASURE_MINOR_ITEM2    "minor item 2"
#define TREASURE_MINOR_ITEM3    "minor item 3"
#define TREASURE_MINOR_ITEM4    "minor item 4"
#define TREASURE_MINOR_ITEM5    "minor item 5"
#define TREASURE_MAJOR_ITEM1    "major item 1"
#define TREASURE_MAJOR_ITEM2    "major item 2"
#define TREASURE_MAJOR_ITEM3    "major item 3"
#define TREASURE_MAJOR_ITEM4    "major item 4"
#define TREASURE_MAJOR_ITEM5    "major item 5"
#define TREASURE_TOP_ITEM       "top item"
#define TREASURE_JUNK           "junk"

#endif