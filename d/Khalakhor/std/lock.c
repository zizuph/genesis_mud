inherit "/std/object";
inherit "/d/Khalakhor/lib/lock";

#include <stdproperties.h>

public void
create_lock()
{
}

nomask void
create_object()
{
    set_name("lock");
    set_pick_difficulty(100);

    add_prop(OBJ_M_NO_GET, "It is firmly attached.\n");
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 200);

    create_lock();
}
