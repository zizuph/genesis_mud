/*******************************************************************************
 * Outside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;
void
create_outpost_outside_room()
{
    set_short("Inside the read gates of the elven Outpost");
    set_em_long("You are now standing inside the rear gates of the elven outpost. " +
        "The large stone wall around the keep protects you " +
        "against the dangers of this area. The air here, smoky " +
        "from burning torches and cooking fires, irritates your nostrils. " +
        "To the east and west you can see the entrances into two tall " +
        "wooden towers that rise from the corners of the walls. To the " +
        "south looms a large octagonal building sitting in the center of " +
        "the outpost.\n");

    add_item( ({"tower", "wooden tower","towers"}),
        "The tower is a made of large logs and small stone blocks. " +
        "They are roughly 30 feet tall and provides an excellent view, as " +
        "well as a great place to launch attacks with ranged weapons.\n");

    add_item( ({"wall" , "stone wall"}),
        "The wall is a made of rough stone blocks. It surrounds the outpost " +
        "providing some protection against invaders.\n");

    add_item( ({"building" , "large building" , "wooden building"}),
        "The building appears to be the hub of this outpost. It is quite " +
        "large and appears to be very well built. A myriad of smells " +
        "including cooking fires and weapon oil are flowing from it, as " +
        "well as the sounds of laughter and the clanging ring of steel " +
        "Striking steel.\n");

    add_exit("gate04.c","north");
    add_exit("netower01.c","east");
    add_exit("nwtower01.c","west");
    add_exit("outpost09.c","south");
}
