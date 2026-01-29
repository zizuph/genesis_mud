/*
 * BREEDOOR + h1door_in.c
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Gondor/defs.h"
#include <filter_funs.h>

#define EXIT    "east"
#define OROOM   "/w/varian/house/office.c"

public void
create_door()
{

    set_door_id("bree_h1_door");
    set_pass_command(EXIT);
    set_door_name(({"wooden door", "door", "sturdy door",
        "sturdy wooden door"}));
/*    set_other_room("/d/Shire/bree/rooms/road/broad03");*/
    set_other_room(OROOM);
    set_door_desc("The sturdy wooden door is the main " +
        "entrance into the townhouse. If you hear " +
        "someone knocking you might examine the window " +
        "to see who is there. On the other side of " +
        "the door is the village of Bree.\n");
    set_fail_pass("The door is securely locked.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_knock_command("knock");
    set_key("bree_h1_key");
    set_no_pick();
}
