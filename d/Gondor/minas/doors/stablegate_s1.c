/*
 *  /d/Gondor/minas/obj/stablegate_s1.c
 *
 *  Inner gate for the entrance to the Royal Stables
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
    set_door_id("southgate");
    set_pass_command(({"n","north"}));
    set_door_name(({"brass gate", "gate"}));
    set_other_room(INNER_MINAS + "/houses/stable1");
    set_door_desc("The large brass gate keeps the horses in the Royal "
        + "Stables from running loose in the streets.\n");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");

}
