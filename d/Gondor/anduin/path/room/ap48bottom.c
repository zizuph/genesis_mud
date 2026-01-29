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
    set_short("Underwater in a river");

    set_long(&long_desc());

    drinkable();

    set_tell_time(50);

    set_no_exit_msg(({"northeast", "east", "southeast"}), 
         "You wander off away from the river but find little of "
         + "interest.\n");
    set_no_exit_msg(({"southwest", "west", "northwest"}), 
         "The swift flow of the mighty Anduin blocks your progress in "
         + "that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
	add_item(({"river", "mighty river", "anduin", "Anduin", "mighty anduin",
        "mighty Anduin", "flow", "swift flow", "water", "waters"}), "The "
        + "swift waters of the mighty Anduin churn all around you.\n");

    add_tell("The swift flow of the river swirls around you.\n");
    add_tell("You struggle against the current.\n");
    add_tell("The water pushes against you.\n");
    add_tell("You tumble over and over in the current.\n");

    set_drink_from(({"river", "anduin", "Anduin", "river anduin", 
        "River Anduin", "flow", "swift flow", "mighty anduin", 
        "Mighty Anduin"}));
}

string
long_desc()
{
    return "Deep under the surface of the River Anduin.\n"; 
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
}

public void
init()
{
    ::init();
    init_drink();
}
