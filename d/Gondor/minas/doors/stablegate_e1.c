/*
 *  /d/Gondor/minas/obj/stablegate_e1.c
 *
 *  Inner door for east stable in Royal Stables
 *
 *  Alto, 10 April 2001
 *
 */


#pragma save_binary

inherit "/std/door";

#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_door()
{
    ::create_door();
    set_door_id("eastgate");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden gate","gate"}));
    set_other_room(INNER_MINAS + "/houses/stable1");
    set_door_desc("This gate is made of solid oak\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");
}
