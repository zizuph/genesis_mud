#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a short section of corridor deep below in the " +
        "temple. An arched entrance to the west leads to a large " +
        "circular room and to the east a guardroom opens up.\n");

    add_exit( DUNGTWO + "guard.c", "east" );
    add_exit( DUNGTWO + "court.c", "west" );
}
