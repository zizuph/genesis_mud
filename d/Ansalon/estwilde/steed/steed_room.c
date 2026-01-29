/* Room for storing steeds when dismissed */

#include "../local.h"
#include <stdproperties.h>

inherit "/d/Ansalon/std/room";

public void
create_ansalon_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("steed room");
    set_long("Room for storing steeds. Should not be open to mortals.\n");
}

public int
query_steed_room()
{
    return 1;
}    
