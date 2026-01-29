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
    set_long("You are standing in Great Hall of Audience. To your northwest " +
        "is the large pilgrim's exit leading out of the temple and to the " +
        "east is an arched opening which is the entrance for the Black " +
        "Dragonarmy. To the north and southeast are two ten-foot high " +
        "platforms facing towards the middle of the vast hall.\n");

    add_item(({"platforms"}),
        "There is a platform slightly to your north and to your southwest. " +
        "Also a higher one towers in the very centre of the hall.\n");

    add_item(({"north platform"}),
        "The platform to the north connects an entrance in the wall to a " +
        "slender bridge of rock which leads directly to the centre of the " +
        "hall.\n");

    add_item(({"southeast platform"}),
        "The platform to the southeast has semi-circular steps leading up to " +
        "it. On top of it stands a large carved chair which looks almost " +
        "like a throne and behind it above an entrance hang the standards " +
        "of the Black Dragonarmy.\n");

    add_item(({"opening", "arched opening"}),
        "This large arched opening is heavily guarded and seems to lead to " +
        "an antechamber for the Black Dragonarmy.\n");

    add_item(({"bridge", "slender bridge"}),
        "It is made of black rock and seems to defy the laws of gravity " +
        "making it seem as if it will break at any moment.\n");

    add_item(({"centre", "middle"}), 
        "A slender bridge of rock from the north reaches a higher platform " +
        "standing in the very centre of this large hall. A set of narrow " +
        "stairs lead up to the platform made from rock curling upward from " +
        "the floor like a giant hooded snake.\n");

    add_item(({"high platform", "higher platform", "snake", "giant hooded snake"}),
        "You would need to step closer to get a better look at it.\n");

    add_exit( TEMPLE + "hall6.c", "south" );
    add_exit( BLACK + "achamber.c", "east" );
    add_exit( TEMPLE + "hall3.c", "west" );
    add_exit( TEMPLE + "hall1.c", "northwest" );
    add_exit( TEMPLE + "altar.c", "southwest" );
}
