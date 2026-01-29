inherit "/std/room";
#include <stdproperties.h>
#include "../defs.h"

void
reset_room()
{
    if (!present("torch"))
        room_add_object(G_OBJ + "torch");
}

create_room() 
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(G_ROOMS + "shop", "east");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

