/* Vladimir 8-16-94 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "local.h"

void
create_room()
{
   set_short("Fortress hallway");
   set_long("You leave the outside world behind you as you enter the fort.\n"
     + "You have arrived at a T intersection, one way leads east, the\n"
      + "other west. You cannot seem to perceive why any creature would\n"
      + "live and operate in an atmosphere such as this. There is trash\n"
      + "lying about in small heaps, decaying and forgotten. While you\n"
    + "do not see any orcs, you certainly can smell them. The idea of\n"
     + "being outside seems much nicer now.\n");
   
   add_item(({"heaps", "trash"}),
    "It is so vile and disgusting that it is hard to tell just what it "+
   "is.\n");
   add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");

   add_exit(ORC+"r1", "east");
   add_exit(ORC+"temple", "north");
   add_exit(ORC+"r3", "west");
   add_exit("/d/Genesis/start/human/wild2/orc_fort", "south");
}
