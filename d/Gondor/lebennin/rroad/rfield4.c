/*     This room is rfield4.c, and it is the room just outside of a 
 *     farmhouse west of Pelargir, just off the ring road.
 *
 *      (C) Copyright Jim Fraser (Theory)
 *
 */

inherit "/d/Gondor/lebennin/rroad/rfield.c";
 
#include <macros.h>
#include <stdproperties.h>
 
#include "/d/Gondor/defs.h";

void
create_field()
{
    set_extraline("The gate leading back to the ring road is just east of "
        + "here, and there is also a door into the farmhouse.");

    add_exit(LEB_DIR + "rroad/rfield2", "east", 0, 2,);
    add_exit(LEB_DIR + "rroad/rfarm", "in", 0, 2,);

    add_field();
    add_house();
    add_walls();
    add_road();
    add_city();
    add_item(({"path", "track",}),BSN("The path is little more than "
        + "matted grass from years of being trodden on. It leads to the "
        + "house in the west."));
    add_item(({"fence","gate",}),BSN("The gate in the fence just east of "
        + "leads back to the ring road encircling Pelargir."));

}
