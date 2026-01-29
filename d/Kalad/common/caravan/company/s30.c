#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Dining Hall");
    set_long("You are inside a grand dining hall.\n"+
      "This room is so huge it seems to go on without end. Huge dining "+
      "tables lie around the western and eastern sides of the room while "+
      "the center is empty. The floor is tiled in brilliant red marble. "+
      "The central portion of this room is covered with a luxuriant carpet. "+
      "High up on the ceiling are crystalline chandeliers. Even the walls "+
      "are not bare for they are covered with beautiful murals. The rest of "+
      "the dining hall lies to the south.\n");

    add_item(({ "tables" }), "Made of the finest mahogany, the tables are "+
      "covered with the finest of silken cloths.\n");

    add_item(({ "carpet" }), "An exotic floor covering, from the designs on "+
      "its surface it seems to have come from the far eastern lands of "+
      "Kalad.\n");

    add_item(({ "chandeliers" }), "Many of them can be seen hanging "+
      "delicately from the ceiling rafters. They provide the majority of "+
      "the illumination in this room.\n");

    add_item(({ "murals" }), "They depict images of the forests and "+
      "mountains.\n");

    add_exit(CVAN + "company/s33", "south");
}
