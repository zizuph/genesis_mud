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

    anorien_add_items();
    path_add_items();
    add_path_tells();
    nindalf_add_items();
    mountain_add_items();
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"north", "northeast", "east"}), 
        "You wander off into the swamp but find little of "
        + "interest.\n");
    set_no_exit_msg(({"south", "southwest", "west"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);

    add_exit(AND_PATH + "ap06", "northwest", 0, 3, 0);
    add_exit(AND_PATH + "ap04", "southeast", 0, 3, 0);
}

string
long_desc()
{
    return "On a well-trodden path across Nindalf near the river Anduin."
        + sky_desc() + "the path as it winds its way through the muddy "
        + "banks of the river. Swamps extend in all directions as far "
        + "as the eye can see to the east of the river, while the green "
        + "fields of Anorien span from the western banks.\n"; 
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
