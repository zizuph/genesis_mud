#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("A small office");
    set_long("This is a small square room with a simple wooden desk " +
        "and chair as the only furniture in it. An archway leads out " +
        "of the room to the east.\n");

    add_item(({"desk", "wooden desk", "simple desk", "simple wooden desk"}),
        "It is a plain desk with a top and four legs completely made " +
        "of wood.\n");
    add_item(({"chair", "wooden chair"}),
        "It is a plain wooden chair with a seat, back and four legs.\n");

    add_exit( RED + "corr3.c", "east");
}
