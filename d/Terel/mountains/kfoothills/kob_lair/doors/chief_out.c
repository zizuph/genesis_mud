/*
 * chief_out.c
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
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_door()
{
    ::create_door();
    set_door_id("kob_chieftain");
    set_pass_command(({"e", "east", "exit", "out"}));
    set_door_name(({"wooden door", "heavy door", 
        "heavy wooden door", "door"}));
    set_other_room(KOB_LAIR_PATH + "kob_lair_a13");

    set_open(0);    
}
 
