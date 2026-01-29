#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("You are close to the great Mordor Gate. To the west, " +
        "you can see the dark shadow of the tower rising further down " +
        "the road. To the north and the south dark narrow streets are " +
        "branching off the road.");
    set_road(2);
    set_side("east");
    add_item(({"gate","mordor gate"}), BSN(
        "To the east, you can see a great gate in an archway under " +
        "the city wall. This is Mordor Gate, the main gate of the city."));
    add_item(({"wall","walls","city wall","city walls"}), BSN(
        "The eastern city walls are not far from here. Where the " +
        "street meets the walls, you can make out a large gate."));

    add_exit(MORGUL_DIR + "city/barrstr3","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/i_egate","east","@@check_exit",2);
    add_exit(MORGUL_DIR + "city/barrstr2","south","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr4","west","@@check_exit",1);
}
