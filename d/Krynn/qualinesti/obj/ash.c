/*
 * ashes.c
 * Pile of ashes found in the campfire.
 *
 * Blizzard, 15/03/2003
 */

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

static int     gAsh;

public void
create_object()
{
    set_name(({"ashes", "ash" }));
    set_short("handful of ashes");
    set_adj(({"gray", "handful", "of" }));
    set_long("A handful of gray ashes.\n");
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 30);
}

public void
remove_ash()
{
    tell_room(E(TO), "A gust of wind blows away the ashes.\n");
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
        if ( gAsh && sizeof(get_alarm(gAsh)) )
            return;
 
        gAsh = set_alarm(60.0, 0.0, &remove_ash());
    }
    else if ( living(dest) && gAsh )
            remove_alarm(gAsh);
}

