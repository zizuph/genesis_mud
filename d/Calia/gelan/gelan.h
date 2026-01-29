
/* 
    this is the include file for all programms in gelan 

    history: 
                5/3/2001    attitude inherit included       Maniac
               16/7/2000    enemies include added           Maniac
               12/4/98      RABBIT_QUEST -> GOPHEROO_QUEST  Maniac
               30/3/97      cadets header added             Maniac
                3/10/95     pillory details added           Maniac
                 7/9/95      POLYMORPH_QUEST added          Maniac
                19.1.95      ALCHEMIST_QUEST added          Maniac
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

/* Properties and defined object names */
#define ATTACKED_GELAN        "_attacked_gelan"
#define LIVE_I_KNOW_CALIA_GELAN_NPCS "_live_i_know_calia_gelan_npcs"
#define PILLORY_OBJ_NAME      "_gelan_pillory_obj"

/* Base paths. */
#define GELAN_PATH            DOMAIN_DIR + "gelan/" 
#define ROAD_DIR              DOMAIN_DIR + "road/"
#define MOUNT_DIR             DOMAIN_DIR + "mountain/"
#define DINO_GELAN            DOMAIN_DIR + "deinonychus/gelan/"
#define GLYKRON_GELAN         DOMAIN_DIR + "glykron/gelan/"
#define MERLIN_GELAN          DOMAIN_DIR + "merlin/gelan/"
#define MANIAC_GELAN          DOMAIN_DIR + "maniac/gelan/"

/* Domain Gelan paths */
#define GELAN_ROOMS           GELAN_PATH + "rooms/"
#define GELAN_OBJECTS         GELAN_PATH + "objects/"
#define GELAN_WEAPONS         GELAN_PATH + "weapons/"
#define GELAN_ARMOURS         GELAN_PATH + "armours/"
#define GELAN_DOORS           GELAN_ROOMS + "doors/"
#define GELAN_SPECIALS        GELAN_PATH + "specials/"
#define GELAN_MONSTERS        GELAN_PATH + "monsters/"
#define GELAN_TEXTS           GELAN_PATH + "texts/"

/* Domain Gelan files */
#define GELAN_ATTITUDE        GELAN_SPECIALS + "attitude"
#define PILLORY_OBJ           GELAN_OBJECTS + "pillory_ob"
#define PILLORY_ROOM          GELAN_ROOMS + "pillory_e"
#define STD_PATROL            GELAN_SPECIALS + "stdpatrol.c"
#define STD_GUARD             GELAN_MONSTERS + "stdguard"
#define STD_AIDED             GELAN_MONSTERS + "stdaided"
#define STD_ROOM              GELAN_ROOMS + "gelanroom"
#define CADET_INCLUDE         "/d/Calia/gelan/cadet/cadet.h"
#define TIMER_INCLUDE         "/d/Calia/gelan/specials/timer.h"
#define GUARD_INCLUDE         "/d/Calia/gelan/specials/guards.h"
#define ROOMS_INCLUDE         "/d/Calia/gelan/rooms/room.h"
#define OBJECT_INCLUDE        "/d/Calia/gelan/objects/object.h"
#define WEAPON_INCLUDE        "/d/Calia/gelan/weapons/weapon.h"
#define ARMOUR_INCLUDE        "/d/Calia/gelan/armours/armours.h"
#define MONSTER_INCLUDE       "/d/Calia/gelan/monsters/monster.h"
#define GELAN_ENEMY_INCLUDE   "/d/Calia/gelan/specials/enemies.h"
#define DOOR_INCLUDE          "/d/Calia/gelan/rooms/doors/door.h"
#define SPECIAL_INCLUDE       "/d/Calia/gelan/specials/specials.h"
#define TOWN_ERRORLOG         GELAN_PATH + "errors.log"

/* Miscellaneous defines */
#define POLYMORPH_QUEST       "/d/Calia/mountain/special/polymorph_quest.h"
#define DEBUG_GELAN
#define GELAN_PATH_END        22
#define GUARD_LOG             "guard.log" 
#define SQUARE_ROOM           GELAN_ROOMS + "square_room.c"
#define HAIR_INCLUDE          "/d/Calia/gelan/specials/hair.h"
#define NUMBER_QUEST          "/d/Calia/gelan/specials/number_quest.h"
#define RABBIT_QUEST          "/d/Calia/gelan/specials/rabbit_quest.h" /* obsolete */ 
#define GOPHEROO_QUEST        "/d/Calia/gelan/specials/gopheroo_quest.h"
#define ALCHEMIST_QUEST       "/d/Calia/gelan/specials/alchemist_quest.h"

#ifndef HAUNT_CODE
#define HAUNT_CODE            "/d/Calia/gelan/specials/haunt_code.h"
#endif

#define DESC(a)		      (GELAN_SPECIALS + "desc")->desc(a)
