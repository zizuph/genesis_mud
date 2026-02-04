/*
    House3.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house3_door");
    set_door_name(({"wooden door", "door"}));
    set_pass_command(({"n","north"}));
    set_open_mess(({"forces the frozen door open.\n", "Someone forces the frozen door open.\n"}));
    set_other_room(CALATHIN_DIR + "houses/house3a");
    set_open(0);
    set_locked(0);
    set_pick(1);
    set_unlock_command("unlock");
}

