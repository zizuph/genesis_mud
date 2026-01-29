inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("key");
    add_name("_kalen_key");
    add_adj("steel");
    add_adj("large");
    set_short("large steel key");
    set_long("This is a large steel key. Somewhere there is a lock waiting to be unlocked with this key.\n");

    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 20);
}

string
unlock_response(string str)
{
    if(str == "All the mysteries of the world")
    {
        notify_fail("You have got the wrong key!\n");
        return 0;
    }
    notify_fail("Unlock what? All the mysteries of the world?\n");
    return 0;
}


public void init()
{
    ::init();
    add_action(unlock_response, "unlock");
}

