/*	rfield1.c
 *	Northern field room off the ring road around pelargir.
 *
 *      Copyright  (C) Jim Fraser    (THEORY)
 *
 *	Revisions  (by)  (date)
 */

inherit "/d/Gondor/lebennin/rroad/rfield.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <stdproperties.h>
 
#include "/d/Gondor/defs.h";

void
create_field()
{
    set_extraline("The field here is just to the west of Pelargir, and "
	+ "there are more fields stretching out to the west. A fence and "
	+ "the river block passage to the north and west, and the city "
	+ "can be seen in the distance to the east.");

    add_exit(LEB_DIR + "rroad/rr5", "east", 0, 2);
    add_exit(LEB_DIR + "rroad/rfield2", "south", 0, 2);


    add_field();
    add_house();
    add_fence("There is a break in the fence to the south.");
    add_sirith("north" , ({"northern arm"}));
    add_walls();
    add_road();
    add_city();
    add_bridge("north");

    set_drink_from(({"river", "sirith", }) );
}

public void
init()
{
    ::init();

    init_drink();
}

