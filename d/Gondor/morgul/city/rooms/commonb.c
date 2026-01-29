/*
 *  The Minas Morgul Common Board Room
 *
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    object board;

    set_extraline(
       "The only feature in this room is a large board. A flight of "
     + "wooden stairs is leading back down to the ground floor.");

    set_road(9);
        set_short_desc("in a board room in Minas Morgul");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item(({"floor","plank","planks", "hole", }), BSN(
        "The floor is made of rough wooden planks. Through a hole, "
      + "a flight of stairs is leading down to the ground floor."));
    add_item(({"wall", "walls", }),
        "The walls are made of roughly hewn stone blocks.");
    add_item(({"stone", "stones", "blocks", "stone blocks"}),
        "They are roughly hewn, large, but almost square.");
    add_item(({"flight", "stairs", "flight of stairs", }), BSN(
        "A flight of wooden stairs is leading down through a hole in "
      + "the floor to the ground floor of the building."));

    add_exit(MORGUL_DIR + "city/rooms/boardroom", "down","@@check_exit");

    board = clone_object("/d/Genesis/obj/board");
    board->move(TO);
}

