/*
 * PELDOOR + h1door_out.c
 *
 * Varian - Aug 2021
 *
 */

#pragma strict_types
#pragma save_binary 


#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Gondor/defs.h"
#include <filter_funs.h>

inherit HOUSE_DOOR;

#define EXIT    "east"
#define OROOM   PEL + "h1_liv.c"

public void
create_door()
{

    set_door_id("pel_h1_door");
    set_pass_command(EXIT);
    set_door_name(({"wooden door", "door", "ornate door",
        "ornate wooden door"}));
    set_other_room(OROOM);
    set_door_desc("This ornate wooden door leads into a large " +
        "and luxurious house in northern Pelargir. If you " +
        "don't have a key, perhaps you could knock and " +
        "see if the owner is home?\n");
    set_fail_pass("A hidden guard steps up and denies you " +
        "entry. You are guided back out onto the streets " +
        "of Pelargir.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_knock_command("knock");
    set_key("pel_h1_key");
    set_house_name("pel1");
    set_no_pick();
}
