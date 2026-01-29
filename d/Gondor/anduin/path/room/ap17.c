/*
  A path in Nindalf near the Anduin.
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

    set_no_exit_msg(({"northeast", "east"}), 
        "You wander off away from the river but find little of "
        + "interest.\n");
    set_no_exit_msg(({"south", "southwest", "west", "northwest"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "To the "
        + "north, the hills of the Emyn Muil rise above the land.\n");
    add_item(({"path", "well-trodden path"}), "The path makes a turn "
        + "here, heading northeast into the hills and south along "
        + "the river.\n");
    add_tell("You hear a distand roaring sound.\n");
    add_tell("A droning sound comes from the north.\n");

    add_exit(AND_PATH + "ap18", "northeast", 0, 3, 0);
    add_exit(AND_PATH + "ap16", "southeast", 0, 3, 0);
}

string
long_desc()
{
    return "On a well-trodden path across a grassy area near the river "
        + "Anduin." + sky_desc() + "the path as it winds its way through "
        + "the muddy banks of the river. Hills rise on either just of the "
        + "river a league north of here.\n"; 
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
