/*
    om_ball_noble.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
    2017-06-04 Malus: Added race name
*/
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    string radj = ({"stout", "proud", "old", "snooty", "fancy",
        "elder"})[random(6)];

    set_name("noble");
    set_adj(radj);
    set_race_name("human");
    set_short(radj + " noble");
    set_long("This is an older nobleman. He looks tall and proud "+
        "of his heritage. He gazes around the room with wise eyes.\n");
    set_stats(({50,60,60,70,80,45}));
    set_skill(SS_DEFENCE,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY,40);
    set_alignment(400);
    set_knight_prestige(-100);

    set_act_time(5);
    add_act("emote downs another glass of champagne.");
    add_act("chuckle");
    add_act("emote talks about the current trading news.");
    add_act("emote thinks about another day in the Market.");
    add_act("scratch chin");
    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("cower");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    add_equipment(({
        NOBLE + "arm/e_leather_pants",
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/leather_shoes",
/* Take this out and see what happens, Sarr
        NOBLE + "arm/gold_chain",
        NOBLE + "arm/ring",
*/
        NOBLE + "wep/jeweled_dagger",
        }));

    // Wield the dagger when attacked
    command("unwield all");
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    command("wield dagger");
    command("shout Guards! Help! Help!");
    set_alarm(3.0, 0.0, "call_guards", enemy);
}

void
call_guards(object enemy)
{
    call_other(ENV(TO), "call_guards", enemy);
}

