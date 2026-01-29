#ifndef _SOLACE_LOCAL_H_
#define _SOLACE_LOCAL_H_

#include "/d/Krynn/common/defs.h"

#define PARENT  SOLACE_DIR
#define TDIR    PARENT + "new_village/"
#define HOUSE   TDIR + "house/"
#define OBJ     TDIR + "obj/"
#define NPC TDIR + "npc/"
#define LOG     TDIR + "log/"
#define STDDOOR "/d/Krynn/std/door"

/* connections to rooms in other directories */
#define C_FOREST        PARENT + "forest/nforest3" /* OK */
#define C_GRAVES    PARENT + "graves/grave_entr" /* OK */
#define C_WILD      "/d/Krynn/wild/east1" /* OK */
#define C_GUILD     PARENT + "guild/maze1"
#define C_LAKE      PARENT + "lake/room/lake1" /* OK */
#define C_SHIP      PARENT + "ship/pier"   /* OK */
/*
#define C_ELF       "/d/Sparkle/area/faerie/rooms/forest/glade"
*/
#define C_ELF           "/d/Sparkle/area/faerie/obj/portal_faerieg"
#define C_SPLAINS       SOLAMN_DIR + "splains/dragon/landing2" /* OK */
#define C_ROAD          "/d/Krynn/solace/road/road1" /* OK */
#define ROOM_TO_NERAKA  NERAKA_DIR + "dragon/landing1" /* OK */

#define RPG_BOARD       LOG + "rpg_board"

#define SOLINROOM       SOLACE_DIR + "std/solace_inbase"
#define SOLOUTROOM      SOLACE_DIR + "std/solace_outbase"
// for rooms on the ground use SOLOUTROOM2
#define SOLOUTROOM2     SOLACE_DIR + "std/solace_outbase2"

#define SOLACE_MASTER   (TDIR + "master")

/* Places to visit */
#define DEFAULT         0
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

/* The wizard(s) responsible for this area */
#define RESPONSIBLE     ({"rastlin"})

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





