/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * treas_out.c
 *
 * Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit "/std/door";
 
/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
public void
create_door()
{
    ::create_door();
    set_door_id("treas");
    set_pass_command(({"w", "west", "exit", "out"}));
    set_door_name(({"iron door", "strong door", "strong iron door", "door"}));
    set_other_room(CASTLE_DIR + "treas_ent");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);    
    set_locked(1);
}
 
