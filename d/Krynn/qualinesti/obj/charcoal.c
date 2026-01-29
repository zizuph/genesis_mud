/*
 * charcoal.c
 * Charcoal found in the campfire.
 *
 * Blizzard, 15/03/2003
 */

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

static int     gDust;

public void
create_object()
{
    set_name(({"charcoal", "coal" }));
    set_short("small piece of charcoal");
    set_pshort("small pieces of charcoal");
    set_adj(({"small", "black", "piece", "of", "dark" }));
    set_long("A small piece of charcoal that left when the campfire " +
        "burned out.\n");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_M_NO_SELL, 1);
}

public void
remove_coal()
{
    tell_room(E(TO), "The small piece of charcoal crumbles into dust.\n");
    TO->remove_object();
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if ( !objectp(dest) )
        return;

    if ( dest->query_prop(ROOM_I_IS) )
    {
        if ( gDust && sizeof(get_alarm(gDust)) )
            return;
 
        gDust = set_alarm(600.0, 0.0, &remove_coal());
    }
    else if ( living(dest) && gDust )
            remove_alarm(gDust);
}

