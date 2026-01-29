/*
 * /d/Gondor/common/guild2/spells/obj/lominen_effect.c
 *
 * needed for Artirith spell
 *
 * Olorin, Nov 1994
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

int     time = 1;

void
create_object()
{
    set_name( "Morgul_Lominen_Effect" );
    add_name( "artirith_ingr1" );

    add_prop( OBJ_I_VOLUME, 0 );
    add_prop( OBJ_I_WEIGHT, 0 );
    add_prop( OBJ_I_NO_DROP, 1 );
    add_prop( OBJ_I_NO_GIVE, 1 );

    set_no_show();
}

void
set_duration( int i )
{
    time = i;
}

void
enter_env( object to, object from )
{
    ::enter_env( to, from) ;

    if (!objectp( to ) || !living( to ))
    {
        remove_object();
        return;
    }

    set_alarm( itof( time ), 0.0, remove_object );
}

void
leave_env( object old, object dest )
{
    ::leave_env( old, dest );
    old->catch_msg( "You cannot cast \"artirith\" any longer!\n" );
}

int
use_component()
{
    remove_object();
    return 1;
}
