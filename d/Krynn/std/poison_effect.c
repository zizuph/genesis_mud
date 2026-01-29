/*
 * Filename:    /d/Krynn/std/poison_effect.c
 * Description: This is the standard poison effect in Krynn,
 *
 * Copyright (c) May 2003 by Daniel W. Mathiasen aka Boron
 *
 */

inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>

public void
create_poison_effect()
{
    set_name("_krynn_poison");
    set_damage(({ POISON_HP, 10 }));
    set_silent(0);

    TO->create_krynn_poison_effect();
}

public void
do_puke()
{
    int stuffed = E(TO)->query_stuffed();

    if ( stuffed > 10 )
    {
        // Here is a litle hack, set_stuffed(..) is static right now
        // if its changed when you revire this code, please fix it up
        // Boron May 2003
        E(TO)->eat_food( -(ftoi( itof(stuffed) / 10.0 )), 0);
        //E(TO)->set_stuffed( ftoi( itof(stuffed) / 10.0 ) );

        E(TO)->command("$puke");
    }
    else
    {
        E(TO)->command("$groan painfully");
    }
}


public void
start_poison()
{
    if ( query_silent() == 0 )
        set_alarm(itof(query_interval()*2), itof(query_interval()*2), do_puke);

    ::start_poison();
}

