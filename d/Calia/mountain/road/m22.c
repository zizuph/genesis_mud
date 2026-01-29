/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           2.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Away to the southeast you can make out an obelisk.\n", 2);
    add_exit(ROAD+"m16", "northwest");
    add_exit(ROAD+"m26", "southwest");
    add_exit(ROAD+"m21", "west"); 
    add_exit(ROAD+"m27", "south");
    add_exit(ROAD+"m28", "southeast");
}
