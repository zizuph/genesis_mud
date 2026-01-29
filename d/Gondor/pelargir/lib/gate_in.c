inherit "/std/door";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();

    set_door_id("Pelargir_Gate_North");
    set_door_name(({"city gate", "north gate","gate","citygate"}));
    set_other_room(PELAR_DIR + "streets/n_gate_out");
    set_door_desc(VBFC_ME("long_desc"));
    set_lock_desc("The gate can be secured with a thick heavy wooden beam.\n");
    set_lock_name(({"beam","beams"}));
    set_lock_command("block-gate-with-beams");
    set_unlock_command("remove-beams");
    set_open(0);
    set_locked(1);
    set_knock_command(0);
}

string
long_desc()
{
    if (open_status)
        return BSN("The iron doors of the gate are open right now. "
          + "Beyond the gate you can see the road outside, and "
          + "the green fields of Lebennin.");
    else if (lock_status)
        return BSN("The gate is closed. On your side of the gate, "
          + "you can see a thick heavy wooden beam securing the gate.");
    else
        return BSN("The gate is closed, but the wooden beam used to "
          + "secure the gate is not in place right now. You might be "
          + "able to open the gate.");
}
    

