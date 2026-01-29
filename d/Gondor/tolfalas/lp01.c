/*
  A grassy running from the Anduin south of Lorien toward the mountains.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/lorien/lib/lor_funcs.c";

#include "/d/Gondor/lorien/lib/lor_defs.h"

public void
create_gondor()
{
    set_short("A grassy path near a forest");

    set_long(&long_desc());

    path_add_items();
    add_path_tells();
    sky_add_items();

    set_tell_time(600);

    set_no_exit_msg(({"southeast", "south", "southwest"}), 
         "You wander off into the grassy field to the north but find "
         + "little of interest.\n");
    set_no_exit_msg(({"north", "northeast", "northwest"}), 
         "The dense woods seem impenatrable.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"path", "faint path"}), "The faint path disappears into the "
        + "tall grass just a few paces to the east and west.\n");
    add_item(({"bank", "banks"}), "The banks of the river are low here, "
        + "making it possible to easily wade into the water.\n");

    add_exit(AND_DIR + "room/an48c", "east", 0, 3, 1);
    add_exit(LOR_ROM + "lp02", "west", 0, 3, 1);

}

string
long_desc()
{
    return "On a grassy path across a field near the river Anduin."
        + sky_desc() + " Disappearing into the tall grass to "
        + "the east and west, the path is barely visible as it "
        + "runs between a vast field to the south and dense "
        + "woods to the north.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
