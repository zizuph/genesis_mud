/*
  A path in the Brown Lands near the Anduin.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";

#include "/d/Gondor/anduin/lib/and_defs.h"

public void
create_gondor()
{
    set_short("A well-trodden path near a river");

    set_long(&long_desc());

    misty_add_items();
    add_path_tells();
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"northeast", "east", "southeast"}), 
        "You wander off away from the river but find little of "
        + "interest.\n");
    set_no_exit_msg(({"southwest", "west", "northwest"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"field", "fields", "sparse field", "sparse fields"}), "Sparse "
        + "fields lie on either side of the river.\n");
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "Just to the "
        + "south, the hills of the Emyn Muil rise above the land.\n");
    add_item(({"trees", "pine trees"}), "Pine trees dot the landscape "
        + "around you.\n");

    add_exit(AND_PATH + "ap27", "north", 0, 3, 0);
    add_exit(AND_PATH + "ap25", "southeast", 0, 5, 0);
}

string
long_desc()
{
    return "On a path across a field in the western parts of Emyn Muil."
        + sky_desc() + "the path as it winds its way through a forest of "
        + "pine trees. The path rises between a few pine trees into "
        + "the hills to the south.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
        river_add_items();
}
