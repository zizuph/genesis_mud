/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest_door.c
 *
 * Generic guest room door.
 *
 * Sorgum 950711
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
    set_door_id("guest_door");
    set_pass_command(({"w", "west"}));
    set_door_name(({"strong wooden door", "strong door", "wooden door",
			"door"}));
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);    
    set_locked(0);
}
 
