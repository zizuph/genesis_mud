/* Make it possible to climb the platform and then have guards attack you 
 * up there if you are not the General or the "right" colour. If the wrong
 * colour, have the guards force you back down and then report the Soldier.
 * Something cool when unauthorized people climb the high platform.
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_hall.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In the Great Hall of Audience");
    set_long("You are standing in Great Hall of Audience. The vast chamber " +
        "spreads out in almost all directions and to the west is a ten-" +
        "foor high platform facing the middle of the hall. To the northwest " +
        "and southwest are two arched openings which are the White and " +
        "Green Dragonarmies' entrances respectively.\n");

    add_item(({"west platform"}),
        "The platform to the west has semi-circular steps leading up to " +
        "it. On top of it stands a large carved chair which looks almost " +
        "like a throne and behind it above an entrance hang the standards " +
        "of the Green Dragonarmy.\n");

    add_item(({"bridge", "slender bridge"}),
        "It is a slender bridge of rock connecting an entrance in the " +
        "northern wall with the high platform in the middle of the hall.\n");

    add_item(({"openings", "arched openings"}),
        "Both of these large arched openings are heavily guarded and seem " +
        "to lead to antechambers for the White and Green Dragonarmies.\n");

    add_item(({"centre", "middle"}), 
        "A slender bridge of rock from the north reaches a higher platform " +
        "standing in the very centre of this large hall. A set of narrow " +
        "stairs lead up to the platform made from rock curling upward from " +
        "the floor like a giant hooded snake.\n");

    add_item(({"middle platform", "high platform", "higher platform", 
               "snake", "giant hooded snake"}),
        "You would need to step closer to get a better look at it.\n");

    add_exit( TEMPLE + "hall2.c", "north" );
    add_exit( TEMPLE + "hall7.c", "south" );
    add_exit( TEMPLE + "altar.c", "east" );
    add_exit( TEMPLE + "hall3.c", "northeast" );
    add_exit( WHITE + "achamber.c", "northwest" );
    add_exit( TEMPLE + "hall8.c", "southeast" );
    add_exit( GREEN + "achamber.c", "southwest" );
}
