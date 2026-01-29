#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are halfway between the great Morgul Gate "
      + "and the tower of Minas Morgul.");
    set_road(2);
    set_side("west");

    add_mountain();
    add_item(({"gate","morgul gate"}), BSN(
        "To the north, you can see the dark Morgul Gate in an archway "
      + "under the city wall."));
    add_item(({"wall","walls","city wall","city walls"}), 
        "To the north you can see the northern city wall with the Morgul Gate.\n");
    add_exit(MORGUL_DIR + "city/mmr1","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr3","south","@@check_exit",2);
}

