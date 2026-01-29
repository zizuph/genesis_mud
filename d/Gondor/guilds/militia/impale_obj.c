/*
 *
 * This is an object that is cloned into a player when they are
 * auto-impaled.
 *
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


/* Global variables */
static int Time = 123;

public void remove_block();


public void
create_object()
{
    set_name("Militia_Impale_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    set_no_show();
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        remove_object();
        return;
    }
    set_alarm(123.0, 0.0, remove_block);
}

void
remove_block()
{
    remove_object();
}
