/*
  A swampy path in Nindalf near the Anduin.
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

    path_add_items();
    add_path_tells();
    marsh_add_items();
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"north", "northeast", "east"}), 
        "You wander off into the swamp but find little of "
        + "interest.\n");
    set_no_exit_msg(({"south", "southwest", "west"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);

    add_exit(AND_PATH + "ap17", "northwest", 0, 5, 0);
    add_exit(AND_PATH + "ap15", "southeast", 0, 5, 0);
}

string
long_desc()
{
    return "On a well-trodden path across a swamp near the river Anduin."
        + sky_desc() + "the path as it winds its way through the muddy banks "
        + "of the river. Swamps extend in all directions as far "
        + "as the eye can see.\n"; 
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
