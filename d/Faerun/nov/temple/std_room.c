inherit "/std/room"; 

#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"


void
create_nov_room()
{ 
}

void
create_room()
{
    create_nov_room(); 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    seteuid(getuid(this_object()));
}