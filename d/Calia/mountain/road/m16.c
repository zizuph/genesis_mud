/* Moorland in the mid-west of Calia.
   Polymorph demon for the quest is in this room.

   Coded by Maniac.

   History: 
           12/9/95    Polymorph demon added here         Maniac
            1.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

object polymorph;

void
reset_room()
{ 
    if (!polymorph) {
        polymorph = clone_object(MOUNTAIN_MONSTERS+"polymorph_demon");
        polymorph->move(this_object());     
        tell_room(this_object(), "A " + polymorph->short() + " appears!\n");
    }
}


void
create_room()
{
    make_the_room("Away to the northwest you can make out an obelisk.\n", 2);
    add_exit(ROAD+"m10", "northwest");
    add_exit(ROAD+"m20", "southwest");
    add_exit(ROAD+"m15", "west"); 
    add_exit(ROAD+"m21", "south");
    add_exit(ROAD+"m22", "southeast");

    reset_room();
}
