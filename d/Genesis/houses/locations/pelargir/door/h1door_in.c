/*
 * PELDOOR + h1door_in.c
 *
 * Varian - Aug 2021
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

#define EXIT    "west"
#define OROOM   "/w/varian/house/office.c"

public void
create_door()
{

    set_door_id("pel_h1_door");
    set_pass_command(EXIT);
    set_door_name(({"wooden door", "door", "ornate door",
        "ornate wooden door"}));
/*    set_other_room("/d/Gondor/pelargir/streets/belfalas04");*/
    set_other_room(OROOM);
    set_door_desc("The ornate wooden door is the main " +
        "entrance into this luxurious home. If you hear " +
        "someone knocking you might examine the window " +
        "to see who is there. On the other side of " +
        "the door is the city of Pelargir.\n");
    set_fail_pass("The door is securely locked.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_knock_command("knock");
    set_key("pel_h1_key");
    set_no_pick();
}
