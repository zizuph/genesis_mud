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
        "spreads out in almost all directions and to the east is a ten-" +
        "floor high platform facing the middle of the hall. To the northeast " +
        "and southeast are two arched openings which are the Black and " +
        "Blue Dragonarmies' entrances respectively.\n");

    add_item(({"east platform"}),
        "The platform to the east has semi-circular steps leading up to " +
        "it. On top of it stands a large carved chair which looks almost " +
        "like a throne and behind it above an entrance hang the standards " +
        "of the Black Dragonarmy.\n");

    add_item(({"openings", "arched openings"}),
        "These large arched openings are heavily guarded and seem to lead " +
        "to the antechambers for the Black and Blue Dragonarmies.\n");

    add_item(({"bridge", "slender bridge"}),
        "It is a slender bridge of rock connecting an entrance in the " +
        "northern wall with the high platform in the middle of the hall.\n");

    add_item(({"centre", "middle"}), 
        "A slender bridge of rock from the north reaches a higher platform " +
        "standing in the very centre of this large hall. A set of narrow " +
        "stairs lead up to the platform made from rock curling upward from " +
        "the floor like a giant hooded snake.\n");

    add_item(({"middle platform", "high platform", "higher platform", 
               "snake", "giant hooded snake"}),
        "You would need to step closer to get a better look at it.\n");

    add_exit( TEMPLE + "hall4.c", "north" );
    add_exit( TEMPLE + "hall9.c", "south" );
    add_exit( TEMPLE + "altar.c", "west" );
    add_exit( BLACK + "achamber.c", "northeast" );
    add_exit( TEMPLE + "hall3.c", "northwest" );
    add_exit( BLUE + "achamber.c", "southeast" );
    add_exit( TEMPLE + "hall8.c", "southwest" );
}
