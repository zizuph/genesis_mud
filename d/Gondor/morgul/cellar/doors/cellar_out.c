inherit "/std/door";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_door()
{
    ::create_door();

    set_door_id("Morgul_Cellar_Exit");
    set_pass_command(({"w","west"}));
    set_door_name(({"steel gate", "gate", "large steel gate", }));
    set_door_desc(BSN("The large gate is made from steel. An emblem has "
      + "been etched into the center of the gate. Except for that etching, "
      + "the surface of the gate is plain and smooth, without visible "
      + "lock and other ornaments."));
    set_other_room(CELLAR_DIR + "pass_1w1");
    set_locked(0);
    set_open(0);

    set_no_pick();

    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("There is no keyhole or lock visible on this side of the gate.\n");
}

