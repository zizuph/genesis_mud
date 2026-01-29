/* Make it possible to climb the platform and then have guards attack you 
 * up there if you are not the General or the "right" colour. If the wrong
 * colour, have the guards force you back down and then report the Soldier.
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_hall.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In the Great Hall of Audience");
    set_long("You are standing in the north end of the Great Hall " +
        "of Audience. To your north is the wide corridor leading " +
        "out of the temple and the hall opens up to your south. On " +
        "the west side of you is a ten-foot high platform facing " +
        "towards the middle of the vast hall and on the east side is a " +
        "slender bridge of rock leading across the hall to the centre.\n");

    add_item(({"platform", "west platform"}),
        "The platform to your west has semi-circular steps leading up to " +
        "it. On top of it stands a large carved chair which looks almost " +
        "like a throne and behind it above an entrance hang the standards " +
        "of the White Dragonarmy.\n");

    add_item(({"bridge", "slender bridge"}),
        "A slender bridge of rock runs from an entrance higher up on this " +
        "northern wall all across the hall to a slightly higher platform " +
        "in the centre of the hall. It is made of black rock and seems to " +
        "defy the laws of gravity making it seem as if it will break at any " +
        "moment.\n");

    add_item(({"centre", "middle"}), 
        "There seems to be a higher platform standing in the very middle of " +
        "this large hall. It is hard to get a good look at it from here.\n");

    add_exit( TEMPLE + "corr3.c", "north" );
    add_exit( TEMPLE + "hall3.c", "south" );
    add_exit( TEMPLE + "hall4.c", "southeast" );
    add_exit( TEMPLE + "hall2.c", "southwest" );
}
