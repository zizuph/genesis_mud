/*
 * lifeguard.c
 *
 * Used in nyreese/cadu_b3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* A baywatcher */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../nyreese/bridgedefs.h"

void check_pos();

void
create_monster()
{
    int i;

    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    set_name("george");
    set_living_name("george");
    set_long("This is the lifeguard. He is very muscular and tanned. " +
	     "He looks confident.\n");
    set_race_name("human");
    set_adj("muscular");

    add_act("smile");
    set_act_time(20);

    set_stats(({ 74, 50, 81, 47, 45, 78 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 60);

    set_alignment(200);

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

    trig_new("%w 'shouts:' %s", "react_shout");
}

int query_knight_prestige() {return -3;}

void
rescue(object obj)
{
    command("dive");
    command("rescue " + obj->query_real_name());
    set_alarm(2.0, 0.0, check_pos);
}

void
pat(object obj)
{
    command("pat " + obj->query_real_name());
}


void
react_shout(string who, string what)
{
    object ob;

    if (extract(what, 0, 3) != "help")
        return;

    ob = present(lower_case(who), find_object(BRIDGEROOM));
    if (ob)
    {
        set_alarm(2.0, 0.0, &pat(ob));
        return;
    }
  
    ob = present(lower_case(who), find_object(WATERROOM));
    if (ob)
    {
        set_alarm(2.0, 0.0, &rescue(ob));
        return;
    }
}

void
check_pos()
{
    if (E(TO) != find_object(BRIDGEROOM))
    {
        if (E(TO) == find_object(WATERROOM))
	{
            command("up");
	}
        else
	{
            move_living(BRIDGEROOM, "to his work");
	}
    }
}
