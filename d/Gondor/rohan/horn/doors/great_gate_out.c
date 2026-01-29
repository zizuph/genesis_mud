inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("greatgate");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({ "great gate", "gate", "gates" }));
    set_other_room(ROH_DIR+"horn/gorge/out_gate");
    set_door_desc(BS("The great gate looks sturdy. It's made of "+
    "timber with great hinges of iron. The gate is reinforced with iron "+
    "bars.\n"));
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("A massive lock.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(8000346);
    set_knock_command(0);
}
