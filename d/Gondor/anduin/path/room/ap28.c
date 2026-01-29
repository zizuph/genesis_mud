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

    brownlands_add_items();
    add_brownlands_tells();
    add_path_tells();
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"east", "southeast", "south"}), 
        "You wander off away from the river but find little of "
        + "interest.\n");
    set_no_exit_msg(({"west", "northwest", "north"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"field", "fields", "sparse field", "sparse fields"}), "Sparse "
        + "fields lie on either side of the river.\n");

    add_exit(AND_PATH + "ap29", "northeast", 0, 3, 0);
    add_exit(AND_PATH + "ap27", "southwest", 0, 3, 0);
}

string
long_desc()
{
    return "On a well-trodden path across a desolate area near the river "
        + "Anduin." + sky_desc() + "the path as it winds its way along "
        + "the barren banks of the river.\n"; 
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
