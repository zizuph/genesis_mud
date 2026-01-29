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
    set_short("A narrow path near a river");

    set_long(&long_desc());

    path_add_items();
    add_path_tells();
    hill_add_items();

    set_tell_time(600);

    set_no_exit_msg(({"northeast", "east", "southeast", "south"}), 
        "As you step off the steep path, the treacherous footing "
        + "makes you realize the path would be safer.\n");
    set_no_exit_msg(({"west", "northwest"}), 
        "The hill is too steep in that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "The hills of "
        + "the Emyn Muil begin to rise above the land here.\n");
    add_item(({"path", "narrow path", "steep path"}), "The path levels "
        + "out to the south, while to the north it becomes even steeper.\n");
    add_item(({"trees", "pine trees"}), "Pine trees dot the landscape "
        + "around you.\n");

    add_tell("You can feel a constant vibration in the ground.\n");
    add_tell("The deep droning sound of a great waterfall comes from "
        + "nearby.\n");

    add_exit(AND_PATH + "ap19", "north", 0, 30, 0);
    add_exit(AND_PATH + "ap17", "southwest", 0, 10, 0);
}

string
long_desc()
{
    return "On a steep path across low hills near the river Anduin."
        + sky_desc() + "the path as it winds its way up the hills "
        + "away from the river. Hills rise on either just of the river "
        + "a league north of here covered sparsely with trees.\n"; 
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
