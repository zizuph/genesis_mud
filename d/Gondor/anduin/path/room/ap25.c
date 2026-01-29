/*
  A path near Nen Hithoel.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";

#include "/d/Gondor/anduin/lib/and_defs.h"

public void
create_gondor()
{
    set_short("A narrow path in a pine forest");

    set_long(&long_desc());

    path_add_items();
    add_path_tells();
    marsh_add_items();
    add_river_tells();

    set_tell_time(600);

    set_no_exit_msg(({"west", "northwest"}), 
        "You wander off into the woods but don't find much of interest.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "The low "
        + "hills of the western part of Emyn Muil lie all around.\n");
    add_item(({"path", "well-trodden path"}), "The path winds between "
        + "between the pine trees, heading downhill to the southwest "
        + "and to the north.\n");
    add_item(({"trees", "pine trees"}), "Pine trees grow thickly "
        + "around you.\n");
    add_item(({"forest", "pine forest"}), "A pine forest covers the "
        + "hills all around you.\n");

    add_exit(AND_PATH + "ap26", "northwest", 0, 10, 0);
    add_exit(AND_PATH + "ap24", "southeast", 0, 5, 0);
}

string
long_desc()
{
    return "On a path across a hill in the western parts of Emyn Muil."
        + sky_desc() + "the path as it winds its way through a forest of "
        + "pine trees.\n"; 
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
