/*
 * /d/Gondor/common/guild2/spells/obj/nenamarth_effect.c
 *
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

int     time = 1;

void
create_object()
{
    set_name( "Morgul_Nenamarth_Effect" );
    add_name( MORGUL_S_NENAMARTH_EFFECT_NAME );
    add_name( "sauthacuith_ingr2" );
    add_name( "sulambar_ingr2" );

    add_prop( OBJ_I_VOLUME, 0 );
    add_prop( OBJ_I_WEIGHT, 0 );
    add_prop( OBJ_I_NO_DROP, 1 );
    add_prop( OBJ_I_NO_GIVE, 1 );

    set_no_show();
}

void
set_duration(int i)
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
    if (old->query_morgul_level() >= MS_SULAM_MIN)
    {
        old->catch_msg( "You cannot cast \"sauthacuith\" or \"sulambar\" "+
            "any longer!\n" );
    }
    else
    {
        old->catch_msg( "You cannot cast \"sauthacuith\" any longer!\n" );
    }
}

int
use_component()
{
    remove_object();
    return 1;
}


