/*
 * This room holds the second door that you need to 
 * do the thief locket quest to get the key to.
 *
 * Lunatari
 */
#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc8", "south");
   add_exit("dc6", "east");

   add_steel_door("steeldoor2",({ "west", "w" }), DROOM+"dcD", "west", CELL_KEY2);
}
