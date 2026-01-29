/*
 * This room holds the second door that you need to 
 * do the thief locket quest to get the key to.
 *
 * This is the inside dcD.c
 *
 * Lunatari
 */
#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dcE", "west");
   add_exit("cg4", "south");

   add_steel_door("steeldoor2",({ "east", "e" }), DROOM+"dc7", "east", CELL_KEY2);
}
