/*
 *     /d/Gondor/rohan/isengard/obj/guardrm2.c
 *
 *     Opus, April 1997
 * 
 *     Copyright (c) by Robert Miller
 *
 *     Modification log:
 *
 */
#pragma save_binary

inherit "/std/door";

#include "/d/Gondor/defs.h"

public void
create_door()
{
    ::create_door();

    set_door_id("guard_door");
    set_pass_command( ({"e", "east"}));
    set_door_name( ({"wooden door", "door"}));
    set_other_room(ISEN_DIR + "tunnel3");
    set_door_desc(BSN(
        "The door is made from a durable wood and is held to "+
        "the wall with large, black hinges. A white hand has been painted "+
        "in the center of the door."));
    set_open(0);
}
