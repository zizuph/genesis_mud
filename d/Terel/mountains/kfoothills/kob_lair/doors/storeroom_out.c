/*
 * storeroom_out.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/cave_defs.h"
inherit "/std/door";
 
/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
public void
create_door()
{
    ::create_door();
    set_door_id("kob_storeroom");
    set_pass_command(({"w", "west", "exit", "out"}));
    set_door_name(({"wooden door", "strong door", "strong wooden door", "door"}));
    set_other_room(KOB_LAIR_PATH + "kob_lair_a11");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);    
    set_locked(1);
}

/*
 * Function name: reset_door
 * Description:   Close and lock the door on reset
 */
public void  
reset_door() 
{
    do_close_door("");    
    do_lock_door("");
}
