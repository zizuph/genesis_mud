/*
 *   This is a door that leads into the corsair captain's office.
 *
 *   This is a door into one of the cells in the corsair manor.
 *
 *   Talisan,  February 1996
 */
inherit "/std/door";

#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("office");
    set_pass_command(({"nw", "northwest"}));
    set_door_name(({"door", "northwestern door", "northwest door"}));
    set_door_desc("The old door is made from an engraved oak wood, "
      + "and is still quite solid.\n");
    set_other_room(POROS_DIR + "manor/office");
    set_open(0);
}
