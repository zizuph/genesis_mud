/*
 * cas_c9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This room is in the southwest corner of the castle. The " +
             "light gets stronger to the north and darker to the east. " +
             "The walls are really dark and you get the feeling that there " +
             "lies a great, evil danger to the north. " +
             "You see exits to the north and to the east. You could also enter " +
             "a tower to your southwest.\n");

    INSIDE;
    add_exit("cas_c5", "north");
    add_exit("cas_c10", "east");
    add_exit("cas_t33", "southwest");
}
