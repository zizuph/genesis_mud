/*
  A path east of the Anduin near Lorien.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/anduin/lib/and_defs.h"

public void
create_gondor()
{
    set_short("A well-trodden path near a river");

    set_long(&long_desc());

    misty_add_items();
    add_path_tells();
    add_river_tells();

    drinkable();

    set_tell_time(600);

    set_no_exit_msg(({"northeast", "east", "southeast"}), 
        "You wander off away from the river but find little of "
        + "interest.\n");
    set_no_exit_msg(({"southwest", "northwest"}), 
        "The swift flow of the mighty Anduin blocks your progress in "
        + "that direction.\n");
    
    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"bank", "banks"}), "The banks of the river are low here, "
        + "making it possible to easily wade into the water.\n");
    set_drink_from(({"river", "anduin", "Anduin", "river anduin", 
        "River Anduin", "flow", "swift flow", "mighty anduin", 
        "Mighty Anduin"}));

    add_exit(AND_PATH + "ap49", "north", 0, 3, 0);
    add_exit(AND_PATH + "ap47", "south", 0, 3, 0);
    add_exit(AND_PATH + "ap48a", "west", 0, 3, 1);
}

string
long_desc()
{
    return "On a well-trodden path across a field near the river "
        + "Anduin." + sky_desc() + "the path as it winds its way along the "
        + "banks of the river, which widens out here. A dense forest "
        + "of tall trees stands on the far shore of the river" 
        + mallorn_desc() +".\n"; 
}

public void
drink_message(string from)
{
    write("You drink some water from the River Anduin.\n"
        + "You feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some water from the River Anduin.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
        river_add_items();
        lorien_add_items();
}

public void
init()
{
    ::init();
    init_drink();
}
