/*
 *	/d/Gondor/common/guild2/spells/obj/ashes.c
 *
 *	Some ashes - all that remains of non-magical blades
 *	after narusse expires
 *
 *	Olorin, February 1996
 */
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static int     Disperse;

public void
create_object()
{
    set_name(({"ashes", "pile" }));
    set_short("pile of ashes");
    set_adj(({"gray", "pile", "of", }));
    set_long("A small pile of ashes.\n");
}

public void
remove_object()
{
    tell_room(ENV(TO), "A sudden gust of wind blows away the ashes.\n");
    ::remove_object();
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!objectp(dest))
        return;

    if (dest->query_prop(ROOM_I_IS))
    {
        if (Disperse && sizeof(get_alarm(Disperse)))
            return;
        Disperse = set_alarm(600.0, 0.0, remove_object);
    }
    else if (living(dest) && Disperse)
            remove_alarm(Disperse);
}



