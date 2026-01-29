/*
  A path near the Rauros.
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
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"northeast", "east", "southeast", "southwest",
        "west", "northwest"}),          
        "You wander off into the woods but don't find much of interest.\n");


    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "To the "
        + "east, the hills of the Emyn Muil rise above the land.\n");
    add_item(({"path", "narrow path", "steep path"}), "The path leads uphill "
        + "to the north and downhill to the south.\n");
    add_item(({"trees", "pine trees"}), "Pine trees crowd the landscape "
        + "around you.\n");

    add_tell("You can feel a constant vibration in the ground.\n");
    add_tell("The deep droning sound of a great waterfall comes from "
        + "nearby.\n");

    add_exit(AND_PATH + "ap21", "north", 0, 30, 0);
    add_exit(AND_PATH + "ap19", "south", 0, 15, 0);
}

string
long_desc()
{
    return "On a steep path in the southwest part of Emyn Muil." 
        + sky_desc() + "the path as it winds its way through the hills "
        + "above the river. Pine trees crowd all around the path.\n"; 
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
