/*
 *  /d/Gondor/guilds/rangers/npc/janitor.c
 *
 *  Janitor for the Ranger Armouries
 *
 *  Coded by Alto, 29 June, 2001
 *
 */
inherit "/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public int   remove_janitor();
public void  take_things();

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE)
        return;
    seteuid(getuid());

    set_adj("busy");
    add_adj("whistling");
    set_pname("janitors");
    set_name("janitor");
    add_name("ranger");

    set_race_name("janitor");

    set_long("This ranger has drawn the thankless duty of cleaning "
        + "up the armoury. Hopefully there is little for him to "
        + "clean up.\n");

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
    set_alarm(3.0, 0.0, &command("smile all"));
    set_alarm(5.0, 0.0, &command("get all"));
}


public int
remove_janitor()
{
    say("The busy whistling male janitor finishes his work and leaves.\n");
    TO->remove_object();
    return 1;
}

