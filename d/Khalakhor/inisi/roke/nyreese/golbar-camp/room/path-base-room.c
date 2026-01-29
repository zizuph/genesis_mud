 /*
  * Base room to inherit in all the path rooms in the camp
  */
#pragma strict_types
#pragma no_clone

#include "defs.h"

inherit "/std/room";

string extra_desc = "";

public string
display_extra()
{
    return extra_desc;
}

public void
add_extra(string extra)
{
    extra_desc = extra;
}

void
create_room()
{
    set_short("on a green path"); 
    set_long("You are on a small path leading through the green surroundings. " +
             "The vegetation is thick, closing in from all sides of the path shielding of the path from the outside.\n"+
             "@@display_extra@@");

    add_item(({"path", "small path"}),
        "The path looks like it has recently been trampled out through the thick vegetation. Signs of " +
        "footprints and broken branches can been seen everywhere.\n");
    add_item(({"surroundings", "green surroundings", "plants", "green plants", "thick plants", "vegetation"}),
        "All around you are green and thick plants making it impossible " +
        "to see much outside the small path.\n");
    add_item(({"signs", "footprints", "branches", "broken branches"}),
        "There are lots of fresh footprints on the ground, and broken branches on both sides, " +
        "showing signs that the small path recently has been trampled up.\n");
    add_item(({"outside"}),
        "You try to look out through the vegetation, but it is too thick to see anything.\n");
}