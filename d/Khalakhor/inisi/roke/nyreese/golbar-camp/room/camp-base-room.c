 /*
  * Base room to inherit in all the rooms of the camp
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
    set_short("warrior camp"); 
    set_long("You are standing in a warrior camp. Several small tents has been " +
             "setup in a pattern throughout the camp to protect from intruders. " +
             "A few small fires has been lit for the warriors to warm themselves.\n" +
             "@@display_extra@@");

    add_item(({"camp"}),
        "It's a warrior camp, setup by small tents.\n");
    add_item(({"tents", "small tents"}),
        "They are made of dirty canvas.\n");
    add_item("pattern",
        "It's a simple but effective pattern, using the tents to shield of the camp " +
        "from the surrounding vegetation.\n");
    add_item(({"fires", "small fires"}),
        "They are small fires spread out here and there for the warriors to keep their warmth. " +
        "They pleasantly heats your skin.\n");

    add_prop(OBJ_I_HAS_FIRE, 1);
}