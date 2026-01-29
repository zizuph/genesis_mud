inherit "/std/door";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();

    set_door_id("Pelargir_Gate_North");
    set_door_name(({"city gate", "north gate","gate","citygate"}));
    set_other_room(PELAR_DIR + "streets/n_gate_in");
    set_door_desc(VBFC_ME("long_desc"));
    set_open(0);
    set_locked(1);
    set_knock_command(0);
}

string
long_desc()
{
    if (open_status)
    {
        return BSN("The city gate of Pelargir is open, its large iron "
          + "doors swung back on steel posts, allowing entrance into "
          + "the capital of Lebennin.");
    }
    else
    {
        return BSN("The city gate of Pelargir is closed. It is made "
          + "of two large iron doors, held up by strong steel posts. "
          + "On each side of the gate is a large tower, and both towers "
          + "are connected by an arch that spans across the gate. "
          + "On top of the arch, there are battlements.");
    }
}


