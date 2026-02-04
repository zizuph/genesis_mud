inherit "/std/room.c";

/*  Coded by Vader on 10/8/92
 *
 *  This room is the exterior entrance to the basement of the mansion.
 *  There may eventually be some NPC's here, but nothing else spectacular.
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
create_room()
{

   set_short("Basement entrance");

   set_long(break_string(
    "You are in the entrance foyer to the basement of the mansion.  Dust " +
    "and cobwebs abound, and light filters in from a small window too small " +
    "to climb through.  There is also a large heating stove here, that is " +  
    "used to heat the entire mansion.  There is a stone hallway to your " +  
    "south, and a small opening to your north.\n", 70));

   add_item(({"large stove", "stove", "heating stove", "large heating stove"}),
    break_string("A large, iron chamber standing off of the ground.  This " +
                 "will burn coal and wood.  There is a large pile of ashes " +
                 "inside the stove, and a little spilled on the floor next " +
          "to the stove as well.\n", 70));

   add_item(({"ashes", "pile of ashes", "large pile of ashes"}),
    break_string("These ashes look as if they were once the remains of wood. " + 
                 " You lack the knowledge to determine their age.\n", 70));

   add_item(({"window", "small window"}), 
    break_string("This window is set into the top of the wall to your north. " +
                 " It is jammed shut, and too small for anything to get " +
                 "through it.\n", 70));

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(BASE + "hall2", "south", 0);

   add_exit(MANSION + "grd/tunnel", "north", 0);


}

