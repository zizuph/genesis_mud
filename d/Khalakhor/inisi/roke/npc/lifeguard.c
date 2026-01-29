/*
 * lifeguard.c
 *
 * Used in nyreese/cadu_b3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* A baywatcher */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

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
    add_name("lifeguard_george");
    add_name("lifeguard");
    set_living_name("george");
    set_short("tanned muscular human");
    set_long("This is the lifeguard. He is very muscular and tanned. " +
             "He looks confident.\n");
    set_race_name("human");
    set_adj( ({ "tanned", "muscular" }) );

    add_act("smile");
    set_act_time(20);

    add_ask("help", "say That's my job. Helping people.", 1);
    add_ask(({"task", "job"}), "say We do not need anymore staff here. " +
            "But maybe the mayor needs some help.", 1);
    add_ask("mayor", "say The mayor is usually found in his office, up in the town.", 1);
    add_ask(({"town", "cadu"}),
            "say Just head north when you get off the bridge.", 1);
    add_ask(({"dive", "diving"}), "say Feel free to use the diving tower.", 1);
    add_ask(({"swim", "swimming"}), "say It's perfectly safe to swim here. " +
            "Hardly any sharks. But stay close to the bridge so " +
            "I can keep an eye on you.", 1);

    set_stats(({ 74, 50, 81, 47, 45, 78 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 60);

    set_alignment(200);

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);
    set_height_desc("tall");
    set_width_desc("lean");
    set_appearance_offset(-20);

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
    command("pat " + OB_NAME(obj) + " on head");
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
    if (ENV(TO) != find_object(BRIDGEROOM))
    {
        if (ENV(TO) == find_object(WATERROOM))
        {
            command("up");
        }
        else
        {
            move_living(BRIDGEROOM, "to his work");
        }
    }
}
#if 0
// FIXA, find out if it's possible to react on shout this way
// It currently is not, but Mercade has plans for say/shout hooks.
void
emote_hook(string emote, object actor, string adverb, object *oblist,
           int cmd_attr, int target)
{
    if (emote != "smile") return;

    set_alarm(2.0, 0.0, &return_smile(actor, target));
}

#endif
