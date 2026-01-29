#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off to the northwest. To the south can be " +
        "seen a grand pair of metal doors with a corridor " +
        "intersecting before it from both sides. Both the floor " +
        "and walls are bare.\n");

    add_exit( DUNGONE + "corr12", "northwest", "@@msg_nw");
    add_exit( DUNGONE + "corr3.c", "south" );
}

int
msg_nw()
{
    write("The passage slopes slightly downwards.\n");
    return 0;
}
