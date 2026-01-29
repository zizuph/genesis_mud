/* this is the include file for all programms in gelan

    history:   20. 2.93     Talon and Guido                 Glykron
               20. 2.93     changed GUARD_LOG               Merlin
               10. 2.93     STD_GUARD change to my dir      Merlin
                8. 2.93     XXX_MONSTERS included *blush*   Merlin
                6. 2.93     minor changes, damax included   Merlin
               25.01.93     macro for descriptions	    Deinonychus
                9. 1.93     defines for std includefiles    Merlin
                2. 1.93     installed RANDOM_CORRECT        Merlin
               20.12.92     included path for doors         Merlin
                7.11.92     created                         Merlin
*/

#include "site.h"
#include "/d/Dville/abbrev.h"

#ifdef AMIGA
/* have to do this for different random functions on sun and amiga, sorry */
#define RANDOM_CORRECT  0
#else
#define RANDOM_CORRECT  1
#endif

#define DEBUG_GELAN
#define GELAN_PATH      "/d/Dville/gelan/"
#define GELAN_PATH_END  15
#define ROAD_DIR        "/d/Dville/road/"
#define STD_GUARD       "/d/Dville/gelan/monsters/stdguard"
#define STD_ROOM        "/d/Dville/gelan/rooms/gelanroom"
#define TIMER_INCLUDE   "/d/Dville/merlin/gelan/specials/timer.h"
#define GUARD_INCLUDE   "/d/Dville/merlin/gelan/specials/guards.h"
#define ROOMS_INCLUDE   "/d/Dville/gelan/rooms/room.h"
#define OBJECT_INCLUDE  "/d/Dville/gelan/objects/object.h"
#define WEAPON_INCLUDE  "/d/Dville/gelan/weapons/weapon.h"
#define ARMOUR_INCLUDE  "/d/Dville/gelan/armours/armour.h"
#define MONSTER_INCLUDE "/d/Dville/gelan/monsters/monster.h"
#define DOOR_INCLUDE    "/d/Dville/gelan/doors/door.h"
#define SPECIAL_INCLUDE "/d/Dville/gelan/specials/special.h"

#define TOWN_ROOMS      GELAN_PATH + "rooms/"
#define TOWN_OBJECTS    GELAN_PATH + "objects/"
#define TOWN_WEAPONS    GELAN_PATH + "weapons/"
#define TOWN_ARMOURS    GELAN_PATH + "armours/"
#define TOWN_MONSTERS   GELAN_PATH + "monsters/"
#define TOWN_DOORS      GELAN_PATH + "rooms/doors/"
#define TOWN_SPECIALS   GELAN_PATH + "specials/"

#define TOWN_ERRORLOG   GELAN_PATH + "errors.log"

/* defines for the different wizzes */

/* Damax */
#define DAMAX_GELAN      "/d/Dville/damax/gelan/"
#define DAMAX_ROOMS      DAMAX_GELAN + "rooms/"
#define DAMAX_OBJECTS    DAMAX_GELAN + "objects/"
#define DAMAX_WEAPONS    DAMAX_GELAN + "weapons/"
#define DAMAX_ARMOURS    DAMAX_GELAN + "armours/"
#define DAMAX_DOORS      DAMAX_GELAN + "rooms/doors/"
#define DAMAX_SPECIALS   DAMAX_GELAN + "specials/"
#define DAMAX_MONSTERS   DAMAX_GELAN + "monsters/"

/* Deinonychus */
#define DINO_GELAN      "/d/Dville/deinonychus/gelan/"
#define DINO_ROOMS      DINO_GELAN + "rooms/"
#define DINO_OBJECTS    DINO_GELAN + "objects/"
#define DINO_WEAPONS    DINO_GELAN + "weapons/"
#define DINO_ARMOURS    DINO_GELAN + "armours/"
#define DINO_DOORS      DINO_GELAN + "rooms/doors/"
#define DINO_SPECIALS   DINO_GELAN + "specials/"
#define DINO_MONSTERS   DINO_GELAN + "monsters/"

/* Glykron */
#define GLYKRON_GELAN       "/d/Dville/glykron/gelan/"
#define GLYKRON_ROOMS       GLYKRON_GELAN + "rooms/"
#define GLYKRON_OBJECTS     GLYKRON_GELAN + "objects/"
#define GLYKRON_WEAPONS     GLYKRON_GELAN + "weapons/"
#define GLYKRON_ARMOURS     GLYKRON_GELAN + "armours/"
#define GLYKRON_DOORS       GLYKRON_GELAN + "rooms/doors/"
#define GLYKRON_SPECIALS    GLYKRON_GELAN + "specials/"
#define GLYKRON_MONSTERS    GLYKRON_GELAN + "monsters/"

/* Guido */
#define GUIDO_GELAN    "/d/Dville/guido/gelan/"
#define GUIDO_ROOMS    GUIDO_GELAN + "rooms/"
#define GUIDO_OBJECTS  GUIDO_GELAN + "objects/"
#define GUIDO_WEAPONS  GUIDO_GELAN + "weapons/"
#define GUIDO_ARMOURS  GUIDO_GELAN + "armours/"
#define GUIDO_DOORS    GUIDO_GELAN + "rooms/doors/"
#define GUIDO_SPECIALS GUIDO_GELAN + "specials/"
#define GUIDO_MONSTERS GUIDO_GELAN + "monsters/"

/* Jestod */
#define JESTOD_GELAN    "/d/Dville/jestod/gelan/"
#define JESTOD_ROOMS    JESTOD_GELAN + "rooms/"
#define JESTOD_OBJECTS  JESTOD_GELAN + "objects/"
#define JESTOD_WEAPONS  JESTOD_GELAN + "weapons/"
#define JESTOD_ARMOURS  JESTOD_GELAN + "armours/"
#define JESTOD_DOORS    JESTOD_GELAN + "rooms/doors/"
#define JESTOD_SPECIALS JESTOD_GELAN + "specials/"
#define JESTOD_MONSTERS JESTOD_GELAN + "monsters/"

/* Merlin */
#define MERLIN_GELAN    "/d/Dville/merlin/gelan/"
#define MERLIN_ROOMS    MERLIN_GELAN + "rooms/"
#define MERLIN_OBJECTS  MERLIN_GELAN + "objects/"
#define MERLIN_WEAPONS  MERLIN_GELAN + "weapons/"
#define MERLIN_ARMOURS  MERLIN_GELAN + "armours/"
#define MERLIN_DOORS    MERLIN_GELAN + "rooms/doors/"
#define MERLIN_SPECIALS MERLIN_GELAN + "specials/"
#define MERLIN_MONSTERS MERLIN_GELAN + "monsters/"

/* Snarf */
#define SNARF_GELAN     "/d/Dville/snarf/gelan/"
#define SNARF_FOUNTAIN  SNARF_GELAN + "fountain/"
/* added 15.02.93 by Snarf */
#define SNARF_ROOMS     SNARF_GELAN + "rooms/"
#define SNARF_OBJECTS   SNARF_GELAN + "objects/"
#define SNARF_WEAPONS   SNARF_GELAN + "weapons/"
#define SNARF_ARMOURS   SNARF_GELAN + "armours/"
#define SNARF_DOORS     SNARF_GELAN + "rooms/doors/"
#define SNARF_SPECIALS  SNARF_GELAN + "specials/"
#define SNARF_MONSTERS  SNARF_GELAN + "monsters/"

/* Talon */
#define TALON_GELAN    "/d/Dville/talon/gelan/"
#define TALON_ROOMS    TALON_GELAN + "rooms/"
#define TALON_OBJECTS  TALON_GELAN + "objects/"
#define TALON_WEAPONS  TALON_GELAN + "weapons/"
#define TALON_ARMOURS  TALON_GELAN + "armours/"
#define TALON_DOORS    TALON_GELAN + "rooms/doors/"
#define TALON_SPECIALS TALON_GELAN + "specials/"
#define TALON_MONSTERS TALON_GELAN + "monsters/"


/* Zawion */
#define ZAWION_GELAN    "/d/Dville/zawion/gelan/"
#define ZAWION_ROOMS    ZAWION_GELAN + "rooms/"
#define ZAWION_OBJECTS  ZAWION_GELAN + "objects/"
#define ZAWION_WEAPONS  ZAWION_GELAN + "weapons/"
#define ZAWION_ARMOURS  ZAWION_GELAN + "armours/"
#define ZAWION_DOORS    ZAWION_GELAN + "rooms/doors/"
#define ZAWION_SPECIALS ZAWION_GELAN + "specials/"
#define ZAWION_MONSTERS ZAWION_GELAN + "monsters/"

/* functions to use the string functions */

/* eventually you'll have to use seteuid(getuid()); before a call */

#define ROOM(a)         (TOWN_SPECIALS + "path")->room_path(a)
#define OBJECT(a)       (TOWN_SPECIALS + "path")->object_path(a)
#define WEAPON(a)       (TOWN_SPECIALS + "path")->weapon_path(a)
#define ARMOUR(a)       (TOWN_SPECIALS + "path")->armour_path(a)
#define DOOR(a)         (TOWN_SPECIALS + "path")->door_path(a)
#define SPECIAL(a)      (TOWN_SPECIALS + "path")->special_path(a)
#define MONSTER(a)      (TOWN_SPECIALS + "path")->monster_path(a)

#define DESC(a)		(SPECIAL("desc"))->desc(a)

#define GUARD_LOG       MERLIN_SPECIALS + "guard.log"
