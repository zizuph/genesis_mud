/*
 *  /d/Gondor/minas/obj/stablegate_s2.c
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
    set_pass_command(({"s","south"}));
    set_door_name(({"brass gate", "main gate"}));
    set_other_room(INNER_MINAS + "/n2crc6");
    set_door_desc("This gate leads south back to Stable Street. Be sure "
        + "to keep it closed. The last thing the Steward needs is horses "
        + "running loose in his streets!\n");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");

}
