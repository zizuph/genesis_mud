/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * gate_w_in.c
 *
 * Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/door";
 
/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
public void
create_door()
{
    ::create_door();
    set_door_id("gate_ent_w");
    set_pass_command(({"e", "east"}));
    set_door_name(({"strong wooden door", "wooden door", "door"}));
    set_other_room(RIBOS_DIR + "castle/gate_ent");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);    
    set_locked(0);
}
 
