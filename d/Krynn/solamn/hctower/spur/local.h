/* created by Aridor 06/20/93 */

#include "/d/Krynn/common/defs.h"
#include "guild.h"
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <composite.h>                   /* take a look in this one */
#include <stdproperties.h>               /* self-explanatory */
#include <formulas.h>                    /* great for values and weights */
#include <wa_types.h>                    /* weapons and armour */
#include <ss_types.h>                    /* skills and stats */
#include <filter_funs.h>                 /* filter functions */

/* Basic rooms! */
#define SPURRM   "/d/Krynn/solamn/hctower/spur/room/std_spur_room"
#define STD2HP   "/d/Krynn/solamn/hctower/spur/room/std_2hp.c"
#define MAPPERRM "/d/Krynn/solamn/hctower/spur/mapper/map_room"

/* Pathnames used: */

/* HC Tower directory paths                            */
#define TOWR      PARENT + "hctower/"
#define SPUR      TOWR + "spur/"
#define LIV       TOWR + "living/"
#define TOBJ      TOWR + "obj/"
/* Knight Spur directory paths                          */
#define SNPC      SPUR + "npc/"
#define SOBJ      SPUR + "obj/"
#define ROOM      SPUR + "room/"  
/* This is the dir path for the Knight Sponsorship Tree */
#define TREE      SPUR + "tree/"
#define MUSEUM_TREE  SPUR + "museum_tree/"

/* Connections to the World:
Vingaard Mountains */
#define VIN_MOUNT  PARENT + "vin_mount/room/road15"
#define SPLAINS    PARENT + "splains/room/road1"


/* Other useful defs: */
#define SL              75
#define LONG    set_long
#define SHORT   set_short    
#define KNIGHT SNPC + "guard"
#define ARCHER  SNPC + "archer_base.c" 
#define PATROL   SNPC + "guard.c"
#define GDOG   SNPC + "g_mastiff.c"
#define SPUR_START  ROOM + "spur_start"

// Key defines
#define LOCK_M    19940001
#define LOCK_1    19940800
#define CELL      19940900
#define CROWN_C_KEY   19941203
#define SWORD_C_KEY   19941204
#define ROSE_C_KEY    19941205

