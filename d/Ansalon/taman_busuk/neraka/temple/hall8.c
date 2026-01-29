#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_hall.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In the Great Hall of Audience");
    set_long("You are standing just south of a high platform in the middle " +
        "of the Great Hall of Audience. The chamber spreads out in all " +
        "other directions and the domed ceiling rises high above you. To " +
        "the south you see the arched opening which is the entrance for the " +
        "Red Dragonarmy.\n");

    add_item(({"opening", "arched opening"}),
        "This large arched opening is heavily guarded and seems to lead to " +
        "an antechamber for the Red Dragonarmy.\n");

    add_item(({"centre", "middle", "platform", "high platform"}), 
        "There seems to be a high platform standing in the very middle of " +
        "this large hall. It is hard to get a good look at it from here.\n");

    add_exit( TEMPLE + "altar.c", "north" );
    add_exit( RED + "achamber.c", "south" );
    add_exit( TEMPLE + "hall9.c", "east" );
    add_exit( TEMPLE + "hall7.c", "west" );
    add_exit( TEMPLE + "hall6.c", "northeast" );
    add_exit( TEMPLE + "hall5.c", "northwest" );
}
