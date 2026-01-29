/* this is the include file for all programms in gelan 

    history:    3/10/95     pillory details added            Maniac
                 7/9/95      POLYMORPH_QUEST added           Maniac
                19.1.95      ALCHEMIST_QUEST added           Maniac
               23.12.94     NUMBER_QUEST added              Maniac
               10.11.94     RABBIT_QUEST added              Maniac
	       17.09.94	    SQUARE_ROOM added               Deinonychus
 	       14.09.94	    DINO_TEXTS added
               13.9.94      various updates                 Maniac
               11.12.93     remove Snarf                    Merlin 
               23. 2.93     My paths.                       Zawion
               20. 2.93     Talon and Guido                 Glykron
               20. 2.93     changed GUARD_LOG               Merlin
               10. 2.93     STD_GUARD change to my dir      Merlin
                8. 2.93     XXX_MONSTERS included *blush*   Merlin
                6. 2.93     minor changes, damax included   Merlin
               25.01.93     macro for descriptions	    Deinonychus
                9. 1.93     defines for std includefiles    Merlin
                2. 1.93     installed RANDOM_CORRECT        Merlin
               20.12.92     included path for doors         Merlin
                7.11.92     created                         Merlin
               24. 9.93     changed pathes                  Merlin
	       24. 9.93     removed damax, zima, guido      Merlin
			    jestod, talon
*/

#include "site.h"
#include "/d/Calia/domain.h"

#ifdef AMIGA
/* have to do this for different random functions on sun and amiga, sorry */
#define RANDOM_CORRECT  0
#else
#define RANDOM_CORRECT  1
#endif

#define ATTACKED_GELAN "_attacked_gelan"   /* property */

#define PILLORY_ROOM "/d/Calia/merlin/gelan/rooms/pillory_e"
#define PILLORY_OBJ "/d/Calia/gelan/objects/pillory_ob"
#define PILLORY_OBJ_NAME "_gelan_pillory_obj"
#define POLYMORPH_QUEST "/d/Calia/mountain/special/polymorph_quest.h"
#define NUMBER_QUEST    "/d/Calia/maniac/gelan/specials/number_quest.h"
#define RABBIT_QUEST    "/d/Calia/maniac/gelan/specials/rabbit_quest.h"
#define ALCHEMIST_QUEST "/d/Calia/maniac/gelan/specials/alchemist_quest.h"
#define DEBUG_GELAN
#define GELAN_PATH      DOMAIN_DIR + "merlin/gelan/" 
#define GELAN_PATH_END  22
#define ROAD_DIR        DOMAIN_DIR + "road/"
#define STD_PATROL      "/d/Calia/merlin/gelan/specials/stdpatrol.c"
#define STD_GUARD       GELAN_PATH + "monsters/stdguard"
#define HAUNT_CODE      "/d/Calia/maniac/gelan/specials/haunt_code.h"
#define STD_AIDED       GELAN_PATH + "monsters/stdaided"
#define STD_ROOM        GELAN_PATH + "rooms/gelanroom"
#define HAIR_INCLUDE    "/d/Calia/glykron/gelan/specials/hair.h"
#define TIMER_INCLUDE   "/d/Calia/merlin/gelan/specials/timer.h"
#define GUARD_INCLUDE   "/d/Calia/merlin/gelan/specials/guards.h"
#define ROOMS_INCLUDE   GELAN_PATH + "rooms/room.h"
#define OBJECT_INCLUDE  GELAN_PATH + "objects/object.h"
#define WEAPON_INCLUDE  GELAN_PATH + "weapons/weapon.h"
#define ARMOUR_INCLUDE  GELAN_PATH + "armours/armour.h"
#define MONSTER_INCLUDE GELAN_PATH + "monsters/monster.h"
#define DOOR_INCLUDE    GELAN_PATH + "doors/door.h"
#define SPECIAL_INCLUDE GELAN_PATH + "specials/special.h"
#define SQUARE_ROOM     "/d/Calia/deinonychus/gelan/rooms/square_room.c"

#define TOWN_ROOMS      GELAN_PATH + "rooms/"
#define TOWN_OBJECTS    GELAN_PATH + "objects/"
#define TOWN_WEAPONS    GELAN_PATH + "weapons/"
#define TOWN_ARMOURS    GELAN_PATH + "armours/"
#define TOWN_MONSTERS   GELAN_PATH + "monsters/"
#define TOWN_DOORS      GELAN_PATH + "rooms/doors/"
#define TOWN_SPECIALS   GELAN_PATH + "specials/"

#define TOWN_ERRORLOG   GELAN_PATH + "errors.log"

/* defines for the different wizzes */

/* Deinonychus */
#define DINO_GELAN      DOMAIN_DIR + "deinonychus/gelan/"
#define DINO_ROOMS      DINO_GELAN + "rooms/"
#define DINO_OBJECTS    DINO_GELAN + "objects/"
#define DINO_WEAPONS    DINO_GELAN + "weapons/"
#define DINO_ARMOURS    DINO_GELAN + "armours/"
#define DINO_DOORS      DINO_GELAN + "rooms/doors/"
#define DINO_SPECIALS   DINO_GELAN + "specials/"
#define DINO_MONSTERS   DINO_GELAN + "monsters/"
#define DINO_TEXTS	DINO_GELAN + "texts/"

/* Glykron */
#define GLYKRON_GELAN       DOMAIN_DIR + "glykron/gelan/"
#define GLYKRON_ROOMS       GLYKRON_GELAN + "rooms/"
#define GLYKRON_OBJECTS     GLYKRON_GELAN + "objects/"
#define GLYKRON_WEAPONS     GLYKRON_GELAN + "weapons/"
#define GLYKRON_ARMOURS     GLYKRON_GELAN + "armours/"
#define GLYKRON_DOORS       GLYKRON_GELAN + "rooms/doors/"
#define GLYKRON_SPECIALS    GLYKRON_GELAN + "specials/"
#define GLYKRON_MONSTERS    GLYKRON_GELAN + "monsters/"

/* Merlin */
#define MERLIN_GELAN    DOMAIN_DIR + "merlin/gelan/"
#define MERLIN_ROOMS    MERLIN_GELAN + "rooms/"
#define MERLIN_OBJECTS  MERLIN_GELAN + "objects/"
#define MERLIN_WEAPONS  MERLIN_GELAN + "weapons/"
#define MERLIN_ARMOURS  MERLIN_GELAN + "armours/"
#define MERLIN_DOORS    MERLIN_GELAN + "rooms/doors/"
#define MERLIN_SPECIALS MERLIN_GELAN + "specials/"
#define MERLIN_MONSTERS MERLIN_GELAN + "monsters/"
#define MERLIN_TEXTS    MERLIN_GELAN + "texts/"

/* Maniac */
#define MANIAC_GELAN     "/d/Calia/maniac/gelan/"
#define MANIAC_ROOMS     "/d/Calia/maniac/gelan/rooms/"
#define MANIAC_OBJECTS   "/d/Calia/maniac/gelan/objects/"
#define MANIAC_WEAPONS   "/d/Calia/maniac/gelan/weapons/"
#define MANIAC_ARMOURS   "/d/Calia/maniac/gelan/armours/"
#define MANIAC_DOORS     "/d/Calia/maniac/gelan/doors/"
#define MANIAC_SPECIALS  "/d/Calia/maniac/gelan/specials/"
#define MANIAC_MONSTERS  "/d/Calia/maniac/gelan/monsters/"
#define MANIAC_TEXTS     "/d/Calia/maniac/gelan/texts/"


/* eventually you'll have to use seteuid(getuid()); before a call */

#define ROOM(a)         (TOWN_SPECIALS + "path")->room_path(a)
#define OBJECT(a)       (TOWN_SPECIALS + "path")->object_path(a)
#define WEAPON(a)       (TOWN_SPECIALS + "path")->weapon_path(a)
#define ARMOUR(a)       (TOWN_SPECIALS + "path")->armour_path(a)
#define DOOR(a)         (TOWN_SPECIALS + "path")->door_path(a)
#define SPECIAL(a)      (TOWN_SPECIALS + "path")->special_path(a)
#define MONSTER(a)      (TOWN_SPECIALS + "path")->monster_path(a)
#define TEXT(a)		(TOWN_SPECIALS + "path")->text_path(a)

#define DESC(a)		(SPECIAL("desc"))->desc(a)

#define GUARD_LOG       "guard.log" 
