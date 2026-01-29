/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/


#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside the front enterance");
    set_em_long("You are inside a small enterance room in a large building. " +
        "There is a nondescript bench on the left side of the room, and a " +
        "rack of some sort on the right side. To the north there is an open " +
        "doorway leading into a large octagonal room. South of you is the main " +
        "courtyard.\n");

    add_item( ({"bench", "nondescript bench"}),
        "This bench is very plain, and made of dark wood. It looks " +
        "sturdy enough to hold a few people.\n");
    add_item( ({"rack"}),
        "This rack appears to be some sort of weapons rack. It is currently empty.\n");


    add_exit("outpost02.c" , "north");
    add_exit("gate02.c" , "south");
}
