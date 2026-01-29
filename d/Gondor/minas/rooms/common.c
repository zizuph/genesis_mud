/*
 * /d/Gondor/minas/rooms/common.c
 *
 * A room for a common board in Minas Tirith.
 *
 * Olorin, Dec 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
    object  board;

    set_short("the Minas Tirith Information Office");
    set_long("This is the Minas Tirith Information Office.\n"
      + BSN("On the board in this office, important announcements "
      + "are made that concern all inhabitants of these realms. "
      + "Except for the exit leading back into the Administration "
      + "Office to the south and the board, there are no other "
      + "features in this room."));

    add_item(({"wall", "walls", }),
        "The walls are painted white and otherwise featureless.\n");
    add_item(({"floor", "ground", }),
	"The floor is smooth and clean.\n");
    add_item(({"ceiling", "roof", }), BSN(
	"The ceiling has been painted white like the walls. An "
      + "iron oillamp is hanging down from the ceiling, providing "
      + "the room with light."));
    add_item(({"lamp", "oillamp", "iron lamp", "iron oillamp", }),
        "A simple iron oillamp hanging from the ceiling. It is out "
      + "of the reach of your arms.\n");
    add_item(({"exit", "door", }), 
	"The exit leading south is just an opening in the wall.\n");

    add_exit(MINAS_DIR + "rooms/mtoffice", "south",  0, 0);

    add_prop(ROOM_I_INSIDE,1);

    board = clone_object("/d/Genesis/obj/board");
    board->move(TO);

}


