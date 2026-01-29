#ifndef _SOLACE_LOCAL_H_
#define _SOLACE_LOCAL_H_

#include "/d/Krynn/common/defs.h"
#include <macros.h>

#ifdef SOLACE_DIR
#undef SOLACE_DIR
#define SOLACE_DIR "/d/Krynn/sol/"
#endif

#define TDIR    SOLACE_DIR
#define HOUSE   TDIR + "house/"
#define OBJ     TDIR + "obj/"
#define NPC     TDIR + "npc/"
#define LOG     TDIR + "log/"
#define STD     TDIR + "std/"
#define ROOMS   TDIR + "rooms/"
#define STDDOOR "/d/Krynn/std/door"


/* import from other domains */
#define SHIREOBJ        "/d/Shire/common/obj/"

/* inherit file (base files) */
#define SOLACE_ROOM_BASE "/d/Krynn/solace/std/outside_base"
#define FOROUTROOM       "/d/Krynn/solace/std/forest_outbase"
#define FORINROOM        "/d/Krynn/solace/std/solace_inbase"
#define SWIM_ROOM       "/d/Krynn/solace/lake/room/swim_room"

/*connections to the world: */
#define NEWSEA     "/d/Krynn/newsea/newsea1"

/* connections to rooms in other directories */
#define C_FOREST        PARENT + "forest/nforest3"      /* OK */
#define C_GRAVES        PARENT + "graves/grave_entr"    /* OK */
#define C_WILD          "/d/Krynn/wild/east1"           /* OK */
#define C_GUILD         PARENT + "guild/maze1"
#define C_LAKE          PARENT + "lake/room/lake1"      /* OK */
#define C_SHIP          PARENT + "ship/pier"            /* OK */
#define C_ELF                    "/d/Genesis/start/elf/glade"
#define C_SOLACE        PARENT + "new_village/main_road1"
#define C_SPLAINS       SOLAMN_DIR + "splains/dragon/landing2" /* OK */
#define C_ROAD                   "/d/Krynn/solace/road/road1" /* OK */

#define ROOM_TO_NERAKA  NERAKA_DIR + "dragon/landing1" /* OK */

#define RPG_BOARD       LOG + "rpg_board"

#define SOLINROOM       TDIR + "std/solace_inbase"
#define SOLOUTROOM      TDIR + "std/solace_outbase"

/* Connection rooms/* Lake */
#define NEAR_PIER   ROOM + "west_road7"

#define SOLACE_MASTER   (TDIR + "master")

/*monster bases*/
#define KAPAK    "/d/Krynn/common/monster/kapak_base"
#define SIVAK    "/d/Krynn/common/monster/sivak_base"
#define MINOTAUR "/d/Krynn/common/monster/minotaur_base"

/*monster tables*/
#define LAKETABLE "/d/Krynn/common/rndtables/tblsolacelake"
#define CAMPTABLE "/d/Krynn/common/rndtables/tblsolacecamp"

/* places to visit /* Forest */

#define DEFAULT      0
#define FOREST       1
#define HILL         2


/* Places to visit /* new village */
#define MAINROAD        1
#define EASTROAD        2
#define WESTROAD        3
#define INTERSECTION    4
#define NSPATH          5
#define SMALLROAD       6
#define PLATFORM        7
#define BRIDGEWALK      8
#define PARK            9
#define CLEARING        10
#define SQUARE          11

/*formulas*/
#define F_PRESTIGE(object)  (object->query_average_stat())*\
                            (object->query_average_stat()/10)
#define PRESTIGE_ME   set_knight_prestige(F_PRESTIGE(TO));
#define ALIGN_ME   set_alignment(-(F_PRESTIGE(TO)/2));

/* The wizard(s) responsible for this area */
#define RESPONSIBLE     ({"boron", "rastlin"})

/* Misc defines */
#define RESETROOM       object gGuard; \
                        public void \
                        reset_solace_room() \
                        { \
              if (!gGuard) \
                            if (!SOLACE_MASTER->query_attacked()) \
                { \
                              if (random(2)) \
                    gGuard = clone_object(NPC + "goblin_guard"); \
                  else \
                    gGuard = clone_object(NPC + "peacekeeper"); \
                  gGuard->move(TO); \
                } \
              else \
              { \
                switch (random(3)) \
                { \
                  case 0: \
                    gGuard = clone_object(NPC + "kapak"); \
                break; \
                  case 1: \
                gGuard = clone_object(NPC + "baaz"); \
                break; \
                  case 2: \
                gGuard = clone_object(NPC + "bozak"); \
                break; \
                } \
                gGuard->move(TO); \
              } \
                        }

#endif _SOLACE_LOCAL_H_





