#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "that opens up in a remote room to the north. For some " +
        "reason it lies far from the main corridor further " +
        "south. There is a rank smell about in the air coming " +
        "from the north. Both the floor and walls are bare.\n");

    add_cmd_item(({"air", "the air"}), "smell", "You sniff in the " +
        "air for a brief moment. It smells like something have " +
        "burned here recently. Not your normal housefire but that " +
        "of an explosion of some kind as the smell is not burnt " +
        "wood but that of sulfur and other components.\n");

    add_exit( DUNGONE + "workshop", "north");
    add_exit( DUNGONE + "corr11", "southeast", "@@msg_se");
}

int
msg_se()
{
    write("The passage slopes slightly upwards.\n");
    return 0;
}
