/*
  A path through the Vales of Anduin.
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
    vale_add_items();
    add_vale_tells();

    set_tell_time(500);

    set_no_exit_msg(({"northeast", "east", "southeast"}), 
        "You wander off away from the river but find little of "
        + "interest.\n");
    set_no_exit_msg(({"southwest", "west", "northwest"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");

    add_tell("Something rustles about in the grasses.");
    add_tell("A few birds fly overhead.");
    add_tell("Some clouds float lazily across the sky.");
    add_tell("A fish jumps in the river.");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);

    add_exit("/w/serif/shirelink2", "north", 0, 3, 0);
    add_exit(AND_PATH + "ap59", "south", 0, 3, 0);
}

string
long_desc()
{
    return "On a well-trodden path across a field near the river "
        + "Anduin." + sky_desc() + "the path as it winds its way along "
        + "the banks of the river.\n"; 
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
