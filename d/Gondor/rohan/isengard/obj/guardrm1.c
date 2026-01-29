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
    set_pass_command( ({"w", "west"}));
    set_door_name( ({"wooden door", "door"}));
    set_other_room(ISEN_DIR + "guardrm");
    set_door_desc(BSN(
      "Even though constructed from solid wood, the door "+ 
      "shows signs of wear and tear. Large, black hinges hold the door "+
      "on the wall. Painted in the center of the door is a large, white "+
      "hand."));
    set_open(0);
}
