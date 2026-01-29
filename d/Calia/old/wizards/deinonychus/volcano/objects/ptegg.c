inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>

#include "object.h"

void
create_object()
{
    set_name("egg");
    set_pname("eggs");
    set_short("pteranodon egg");
    set_pshort("pteranodon eggs");
    set_adj("pteranodon");
    set_long("It's a pteranodon egg. That means that a pteranodon has laid "
        + "this egg.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 50);
}

void
init()
{
    add_action("eat_egg","eat");
}

int
eat_egg(string str)
{
    object *ob; /* the objects with the name <str> */
    
    /* Is it this egg the player's trying to eat or something else */
    notify_fail("Eat what?\n");
    if (!sizeof(ob = FIND_STR_IN_OBJECT(str, TP)) || ob[0] != TO)
        return 0;
    
    else {
        write(BS("You don't want to be the cause why pteranodons became "
            + "extinct, so you decide not to eat the egg.\n"));
        return 1;
    }
}

