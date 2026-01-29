/*
 *  /d/Gondor/minas/obj/stablegate_n1.c
 *
 *  Inner gate for the north stable in Royal Stables
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
    set_door_id("northgate");
    set_pass_command(({"s","south"}));
    set_door_name(({"gilded gate", "gate"}));
    set_other_room(INNER_MINAS + "/houses/stable1");
    set_door_desc("This gate bears the insignia of the "
        + "House of Elendil. In days past, the mount of the heirs of "
        + "Anarion were stabled here. Now it stands ever empty.\n");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");

}
