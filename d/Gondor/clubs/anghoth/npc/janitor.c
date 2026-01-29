/*
 *  janitor.c
 *
 *  Janitor for the Anghoth club rooms
 *    This NPC will prevent closed club rooms from being used
 *    as de facto drop rooms. No taxes, no drop room.
 *
 *  Alto, 04 June 2002
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <money.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"

public int   remove_janitor();
public void  take_things();

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("slouching");
    add_adj("hunch-backed");
    set_pname("slaves");
    set_name("slave");
    add_name("janitor");

    set_race_name("slave");

    set_long("This slave has drawn the wretched chore of cleaning "
        + "up the quarters of the Anghoth. Hopefully there is little for "
        + "him to clean up.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(50+rnd*10);

    set_gender(0);
    set_skill(SS_AWARENESS, 100);

    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_m_out("pushes his broom");
    set_m_in("pushes his broom in");

    take_things();

    set_alarm(10.0, 0.0, &remove_janitor());

    refresh_mobile();
}


public void
take_things()
{
    set_alarm(3.0, 0.0, &command("scowl all"));
    set_alarm(5.0, 0.0, &command("get all"));
}


public int
remove_janitor()
{
    say("The slouching hunch-backed male slave finishes his work and "
        + "leaves.\n");
    TO->remove_object();
    return 1;
}

