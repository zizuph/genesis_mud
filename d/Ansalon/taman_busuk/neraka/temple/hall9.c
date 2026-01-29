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
    set_long("You are standing in Great Hall of Audience. The vast chamber " +
        "spreads out in almost all directions and to the south is a ten-" +
        "foor high platform facing the middle of the hall. To the east " +
        "and southwest are two arched openings which are the Blue and " +
        "Red Dragonarmies' entrances respectively.\n");

    add_item(({"south platform"}),
        "The platform to the south has semi-circular steps leading up to " +
        "it. On top of it stands a large carved chair which looks almost " +
        "like a throne and behind it above an entrance hang the standards " +
        "of the Red Dragonarmy.\n");

    add_item(({"openings", "arched openings"}),
        "These large arched openings are heavily guarded and seem to lead " +
        "to the antechambers for the Blue and Red Dragonarmies.\n");

    add_item(({"centre", "middle"}), 
        "A high platform stands in the very centre of this large hall.\n");

    add_item(({"middle platform", "high platform", "higher platform", 
               "snake", "giant hooded snake"}),
        "You would need to step closer to get a better look at it.\n");

    add_exit( TEMPLE + "hall6.c", "north" );
    add_exit( BLUE + "achamber.c", "east" );
    add_exit( TEMPLE + "hall8.c", "west" );
    add_exit( TEMPLE + "altar.c", "northwest" );
    add_exit( RED + "achamber.c", "southwest" );
}
