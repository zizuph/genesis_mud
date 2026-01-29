/*
 * /waterdeep/areas/south_highroad/defs.h
 * Definitions pertaining to the Southern High Road outside of the City of
 * Waterdeep
 *
 * Created by Brine jan 2021
 */

// Bring in upper level definitions
#include "../defs.h"

// Southern high road dirs
#define SOUTH_HIGHROAD_STD        (SOUTH_HIGHROAD_DIR + "std/")
#define SOUTH_HIGHROAD_DOC        (SOUTH_HIGHROAD_DIR + "doc/")
#define SOUTH_HIGHROAD_LOG        (SOUTH_HIGHROAD_DIR + "log/")
#define SOUTH_HIGHROAD_ARM        (SOUTH_HIGHROAD_DIR + "armours/")
#define SOUTH_HIGHROAD_WEP        (SOUTH_HIGHROAD_DIR + "weapons/")
#define SOUTH_HIGHROAD_OBJ        (SOUTH_HIGHROAD_DIR + "objects/")
#define SOUTH_HIGHROAD_NPC        (SOUTH_HIGHROAD_DIR + "mobiles/")
#define SOUTH_HIGHROAD_ROOM       (SOUTH_HIGHROAD_DIR + "rooms/")

// Southern high road standard objects
#define SOUTH_HIGHROAD_STD_ROOM   (SOUTH_HIGHROAD_STD + "shr_room")
#define SOUTH_HIGHROAD_STD_INDOOR (SOUTH_HIGHROAD_STD + "shr_room_indoor")

// Southern high road terrain constants
#define DIRT_ROAD                 "Dirt road"
#define HIGH_ROAD                 "High road"

// Southern high road area constants
#define MOUNT_SAR                 "Mount Sar"
#define MOUNT_HELIMBRAR           "Mount Helimbrar"
#define RED_ROCKS                 "Red rocks"
#define RED_CLIFFS                "Red cliffs"
#define WESTWOOD                  "Westwood"
#define ON_ROAD                   "On the High Road"
#define ALONG_ROAD                "Along the High Road"

// Southern high road specific properties
#define SOUTH_HIGHROAD_AREA     "_room_s_south_highroad_area"

// Link to Waterdeep
#define WATERDEEP_LINK          WATERDEEP_DIR + "areas/fieldward/rooms/fork"
