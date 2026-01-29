/*
    of_ball_noble.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    string radj = ({"shrewd", "small", "old", "snooty", "fancy",
        "elder"})[random(6)];

    set_race_name("human");
    set_name("noblewoman");
    set_adj(radj);
    set_short(radj + " noblewoman");
    set_long("This is an older noblewoman. She seems secure in her "+
        "husbands power and wealth.\n");
    set_gender(1);

    set_stats(({30,40,40,70,80,35}));
    set_skill(SS_DEFENCE, 50);
    set_alignment(400);
    set_knight_prestige(-100);

    set_act_time(5);
    add_act("chuckle");
    add_act("smile");
    add_act("emote toys with her necklace.");
    add_act("say Wonderful darling!");
    add_act("emote talks about the latest fashions.");
    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("cower");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    add_equipment(({
        NOBLE + "arm/silk_skirt",
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/high-heels",
        NOBLE + "arm/pearl_necklace",
        NOBLE + "arm/ring",
        NOBLE + "arm/expensive_hat",
        }));
}

void
attacked_by(object enemy)
{
    command("shout Guards! Help! Help!");
    set_alarm(3.0, 0.0, "call_guards", enemy);
    ::attacked_by(enemy);
}
void
call_guards(object enemy)
{
    call_other(ENV(TO), "call_guards", enemy);
}

