/*
 * Kalaman Dungeon Include
 * 
 * Lunatari of Krynn
 *
 * 2008-01-30:
 */
#include "/d/Ansalon/common/defs.h"
//#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#ifndef CLOCK
#define CLOCK "/d/Krynn/common/clock/clock"
#endif

#define CELL_KEY1 "_kalaman_cell_key1_"
#define CELL_KEY2 "_kalaman_cell_key2_"

/* Paths for Sewers */
#define SEWERS_FIRST  SROOM + "first/"
#define SEWERS_SECOND SROOM + "second/"

/* Room definitions for the dungeon_room_base */
#define ROOM_MAIN    0
#define ROOM_CELL1   1
#define ROOM_CELL2   2
#define ROOM_GUARD1  3
#define ROOM_GUARD2  4
#define ROOM_CLROW1  5
#define ROOM_CLROW2  6
#define ROOM_TUNNEL1 7 
#define ROOM_TUNNEL2 8
#define ROOM_WELL    9

/* PLAYER PROP */
#define PLAYER_PEEKED "_i_am_a_peeker_of_holes_"

/* SURRENDER OBJECT */
#define SURRENDER_OBJECT DOBJ + "dungeon_surrender"

/* MASTER DOOR SETTINGS
 *
 * CDSTATUS
 *
 * 0 unlocked, open
 * 1 unlocked, closed
 * 2 locked, closed
 *
 * CDKEY the key that needs to be used
 */
#define S_CDSTATUS(xxx) "cell_door_"+xxx+"_status"
#define S_CDKEY(xxx)    "cell_key_"+xxx+"_key"
