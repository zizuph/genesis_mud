/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/


#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("A large octagonal chamber");
    set_em_long("You are inside a huge octagonal room. There are a few benches strewn " +
        "about the room, and a large banner hangs from the ceiling of the room. " +
        "The exit to the north looks like it leads out into a small chamber " +
        "while the rest of the exits look to lead into other parts of the main " +
        "structure. There is a small staircase leading up into " +
        "the ceiling in the center of the room.\n");

    add_item( ({"benches" , "nondescript benches"}),
        "These benches are very plain, and made of dark wood. They looks " +
        "sturdy enough to hold a few people, and are strewn about the room.\n");

    add_item( ({"stairs" , "straicase"}),
        "These stairs are at a tight, steep angle and lead into a hole in the ceiling.\n");

    add_item( ({"banner"}),
        "The banner that hangs from the ceiling proudly bears the sigil of Telberin " +
        "upon it's silvery cloth.\n");


    add_exit("outpost09.c" , "north");
    add_exit("outpost03.c" , "northeast");
    add_exit("outpost04.c" , "east");
    add_exit("outpost05.c" , "southeast");
    add_exit("outpost01.c" , "south");
    add_exit("outpost06.c" , "southwest");
    add_exit("outpost07.c" , "west");
    add_exit("outpost08.c" , "northwest");
    add_exit("outpost10.c" , "up");

}
