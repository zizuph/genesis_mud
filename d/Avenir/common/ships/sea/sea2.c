inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("out to sea");
    set_long("There is little to see here but water.  The sun shines " +
             "warm upon your back, and a cooling breeze flirts with " +
             "the full sails.\n"); 

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}  
