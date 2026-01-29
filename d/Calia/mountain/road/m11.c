/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           1.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Away to the northwest you can make out an obelisk.\n", 2);
    add_exit(ROAD+"m06", "north");
    add_exit(ROAD+"m05", "northwest");
    add_exit(ROAD+"m07", "northeast"); 
    add_exit(ROAD+"m12", "east");
    add_exit(ROAD+"m17", "southeast");
}
