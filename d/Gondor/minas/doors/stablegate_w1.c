/*
 *  /d/Gondor/minas/obj/stablegate_w1.c
 *
 *  Inner door for west stable in Royal Stables
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
    set_door_id("westgate");
    set_pass_command(({"e","east"}));
    set_door_name(({"bronzed gate","gate"}));
    set_other_room(INNER_MINAS + "/houses/stable1");
    set_door_desc("This gate bears the insignia of the House "
        + "of Stewards. The mount of the Lord Steward is stabled here, "
        + "ever ready for the summons of its master.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_knock_command("knock");
}
