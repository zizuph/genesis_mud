/*
 *   /d/Gondor/ithilen/poros/obj/door.c
 *
 *   This is the door in the corsair captain's office.
 *
 *   Talisan,  February 1996
 */
inherit "/std/door";

#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("office");
    set_pass_command(({"se", "southeast"}));
    set_door_name(({"door", "southeast door", "southeastern door"}));
    set_door_desc("The old door is made from an engraved oak wood, "
      + "and is still quite solid.\n");
    set_other_room(POROS_DIR + "manor/barracks");
    set_open(0);
}
