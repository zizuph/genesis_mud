/*
 * th_2.c
 *
 * This is the board room for the town hall of port macdunn.
 *
 * Khail - June 4/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";

public int *
query_local_coords()
{
    return ({9,4});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
create_khalakhor_room()
{
    set_short("board room");
    set_long("   You've entered a meeting room of some sort, " +
        "judging by the large bulletin board here. " +
        "This is probably where the Lord of the region " +
        "holds public meetings and makes various " +
        "proclomations and notices. Furnishings are " +
        "non-existant, however, it seems that the Lord " +
        "isn't very eager to have people linger after " +
        "he's completed his announcements.\n");

    add_item(({"walls"}),
        "The walls of the building a covered in well crafted "+
        "wooden panels.\n");
    add_item(({"panels", "wooden panels"}),
        "The panels are the product of a master carpenter, "+
        "quite possibly made from oak.\n");
    add_item(({"ground", "floor"}),
        "The floor of the room has been constructed from " +
        "tightly-jointed planks.\n");
    add_item(({"planks"}),
        "Judging from the amount of wear, this room " +
        "receives both a lot of visitors, as well as " +
        "upkeep to maintain the strength of the flooring.\n");
    add_item(({"ceiling"}),
        "The ceiling is lightly arched, and covered in " +
        "the same panels which adorn the walls.\n");

    INSIDE;

    add_exit(ROOM + "th_2", "west");

    reset_euid();
    clone_object(OBJ + "village_board")->move(TO);
}
