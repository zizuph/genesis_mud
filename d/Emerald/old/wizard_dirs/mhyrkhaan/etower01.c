/*******************************************************************************
 * Outside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"
inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("Outside the eastern tower.");
    set_em_long("You are now standing outside the eastern tower of the elven " +
       "outpost. The tower rises high into the air, although only made " +
       "of large logs and a few stones, it appears to be very sturdy. " +
       "You can see. To the west you see the gates of this outpost. " +
       "Directly in front of you there is a small ladder leading up to " +
       "an access hatch in the floor of the tower.\n");

    add_item( ({"tower", "wooden tower","east tower"}),
        "The tower is a made of large logs and small stone blocks. " +
        "It is roughly 30 feet tall and provides an excellent view, as " +
        "well as a great place to launch attacks with ranged weapons.\n");


    add_exit("gate02","west");
    add_exit("etower02","up");
}
