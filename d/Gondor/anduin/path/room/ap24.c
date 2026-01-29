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
        "The hill is too steep in that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "The low "
        + "hills of the western part of Emyn Muil lie all around.\n");
    add_item(({"path", "narrow path"}), "The narrow path winds around "
        + "the eastern shore of the lake.\n");
    add_item(({"trees", "pine trees"}), "Pine trees crowd the hills "
        + "and both shores of the lake.\n");
    add_item(({"forest", "pine forest"}), "A pine forest covers the "
        + "hills all around you.\n");
    add_item(({"lake", "placid lake", "nen hithoel", "Nen Hithoel", 
        "waters", "river", "anduin", "Anduin", "river anduin", "cool waters",
        "River Anduin", "south end", "southern end"}), "The waters of "
        + "the River Anduin pools here into the placid lake Nen Hithoel. "
        + "The cool waters are stopped by the bulk of Emyn Muil "
        + "as they pass southward toward the sea.\n");

    add_exit(AND_PATH + "ap25", "northwest", 0, 10, 0);
    add_exit(AND_PATH + "ap23", "southwest", 0, 5, 0);
}

string
long_desc()
{
    return "On a narrow path on the east of Nen Hithoel." + sky_desc() 
        + "the path as it winds its way through the trees. The waters "
        + "of Nen Hithoel are visible through the trees to the southwest, "
        + "while the path continues northwest into the hills. Further south, "
        + "you can barely make out two large hills looming over the south "
        + "end of the lake.\n"; 
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
