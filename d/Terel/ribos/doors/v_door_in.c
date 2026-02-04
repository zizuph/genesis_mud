/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * v_door_in.c
 *
 * The door to the vault in the ribos bank
 *
 * Vader
 * Recoded by Sorgum 950707
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
    set_door_id("vault_door");
    set_pass_command(({"w","west"}));    
    set_door_name(({"vault door", "door"}));
    set_door_desc("A bank vault made of thick steel.\n");
    set_other_room(RIBOS_DIR + "vault");    
    set_lock_name("lock");
    set_lock_desc("It's a combination lock.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"pulls the door open.\n",
			"Someone opens the vault door.\n"}));
    
    set_lock_command("lock");
    set_unlock_command(({"dial", "11-21-07"}));
    
    set_open_desc("A bank vault door that someone has left open.\n");
    set_closed_desc("A bank vault door that has been left closed.\n");
    
    set_open(0);
    set_locked(1);
}
