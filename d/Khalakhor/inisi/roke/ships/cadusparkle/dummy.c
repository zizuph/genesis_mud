#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../../defs.h"

void
create_room()
{
    set_short("Dummy");
    set_long("A dummy room for the boat to connect to while working.\n");
}
