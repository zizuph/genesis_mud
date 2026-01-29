/*
 * monk_board.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*Ged, Gresolle and Glindor. Wonder who did most ? */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

public void
create_room()
{

    set_short("meeting room");

    set_long("This is the meeting room of the monastery. Here the monks " +
             "gather to discuss various matters, concerning religion, " +
             "adventuring and the world in general. A small opening in " +
             "the north wall leads to the chapel and east of here is a " +
             "small library.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_exit("monk_chapel", "north");
    add_exit("monk_entr", "west");
    add_exit("monk_lib", "east");

    INSIDE;
}
