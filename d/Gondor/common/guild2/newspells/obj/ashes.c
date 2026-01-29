/*
 *    /d/Gondor/common/guild2/newspells/obj/ashes.c
 *
 *    Some ashes - all that remains of non-magical blades
 *    after narusse expires
 *
 *    Olorin, February 1996
 */
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static int Disperse = 0;

public void
create_object()
{
    set_name( ({ "ashes", "pile" }) );
    set_short( "pile of ashes" );
    set_pshort( "piles of ashes" );
    set_adj( ({ "gray", "pile", "of", }) );
    set_long( "A small pile of ashes.\n" );
}

public void remove_object()
{
    tell_room( environment( this_object() ),
        "A sudden gust of wind blows away the ashes.\n");
    ::remove_object();
}

public void enter_env( object dest, object old )
{
    ::enter_env(dest, old);

    if (!objectp( dest ))
    {
        return;
    }
    if (dest->query_prop( ROOM_I_IS ))
    {
        if (Disperse > 0)
        {
            return;
        }
        Disperse = set_alarm( 600.0, 0.0, remove_object );
    }
    else if (living( dest ) && Disperse)
    {
        remove_alarm( Disperse );
    }
}

