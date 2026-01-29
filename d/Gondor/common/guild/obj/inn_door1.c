#pragma save_binary

#include "/d/Gondor/defs.h"

inherit "/std/door";

public void
create_door()
{
    ::create_door();
    set_door_id("inndoor");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(RANGER_DIR + "gondor/rangerinn");
    set_door_desc("The door is made of solid oak. 'The Seven Stars Inn' is written on\n"+
      "it in white paint. You hear song and laughter from behind it.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_key(912873465);
    set_knock_command("knock");
}
