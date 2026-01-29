/*
 *  /d/Gondor/minas/obj/stablegate_e2.c
 *
 *  Stable for the errand-riders of Gondor
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
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden gate"}));
    set_other_room(INNER_MINAS + "/houses/stable4");
    set_door_desc("This gate leads to the place where "
        + "the mounts of the errand-riders are stabled. This is also "
        + "the stable in which the horses of ambassadors and other "
        + "important guests of the Lord of the city are housed.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");

}
