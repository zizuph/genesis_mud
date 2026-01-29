/*
 *   /d/Gondor/ithilien/poros/obj/door_cell.c
 *
 *   This is a door into one of the cells in the corsair manor.
 *
 *   Talisan,  February 1996
 */
inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
    set_door_id("cell3");
    set_pass_command(({"ne", "northeast"}));
    set_door_name(({"cell door", "door"}));
    set_other_room(POROS_DIR + "manor/cellar");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("Corsairs_Cell_Key");
    set_pick(60);
}
