/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           28.4.95          Created                      Maniac
           10.3.99          Wanderer & reset_room added  Uhclem
*/

#pragma save_binary
#define WANDERER "/d/Calia/pond/npcs/wanderer"

inherit "/d/Calia/std/std_west_moor";
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

object Wanderer;

void
create_room()
{
    make_the_room("Away to the southwest you can make out an obelisk, " +
                  "and away to the east you can see a road.\n", 2);   
    add_exit(ROAD+"road18", "northeast");
    add_exit(ROAD+"road17", "east");
    add_exit(ROAD+"m07", "southeast");
    add_exit(ROAD+"m06", "south"); 
    add_exit(ROAD+"m05", "southwest");
}

void
reset_room()
{

    if (!objectp(Wanderer))
    {
        Wanderer = clone_object(WANDERER);
        Wanderer->equip_me();
        Wanderer->move(this_object());
        tell_room(this_object(),
            QCNAME(Wanderer) + " wanders into view.\n");
    }
}
