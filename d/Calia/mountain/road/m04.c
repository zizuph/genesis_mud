/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           28.4.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

object gopheroo;

void
reset_room()
{
     if (!gopheroo) {
          gopheroo = clone_object(MOUNTAIN_MONSTERS+"gopheroo");
          gopheroo->move_living("", this_object());
     }
}


void
create_room()
{
    make_the_room("Away to the southeast you can make out an obelisk.\n",
                   2);
    add_exit(ROAD+"m03", "west");
    add_exit(ROAD+"m08", "southwest"); 
    add_exit(ROAD+"m09", "south");
    add_exit(ROAD+"m10", "southeast");
    reset_room();
}
