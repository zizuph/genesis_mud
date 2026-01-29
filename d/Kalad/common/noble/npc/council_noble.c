/*
    council_noble.c
    
    Code by Sarr,
    recoded by Fysix, Feb 1998
 */
/* 2017-06-04 Malus: Added race name */

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    object wep, arm;

    set_name("member");
    add_name("noble");
    set_adj("noble");
    add_adj("council");
    set_race_name("human");
    set_short("noble council member");
    set_long("This tall and stout nobleman is dressed in his traditional"+
      " robes. He seems to be debating the issue at hand.\n");
    set_stats(({60,70,60,90,90,40}));
    set_skill(SS_DEFENCE,50);
    set_alignment(300 + random(300));
    set_knight_prestige(-150 -random(150));

    set_act_time(5);
    add_act("shout I say! We must not give in to those savage beasts "+
      "in the mountain!");
    add_act("say I'm tired of letting those hoodlums run around freely "+
      "in our city! Its time to take action!\n");
    add_act("think consequences of the actions.");
    add_act("ponder the debate.");
    add_act("say If only we had more time....");
    add_act("say Trade should not be the only issue considered!");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    arm = clone_object(CVAN + "arm/skrobe");
    arm->move(TO, 1);
    arm->set_long("This robe is used by the council members of the "+
      "High Council. It is finely woven, with the insignia of the "+
      "High Lord on shoulder.\n");
    command("wear all");

    // wield when attacked    
    wep = clone_object(NOBLE + "wep/silver_dagger");
    wep->move(TO, 1);
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    command("wield all");
    command("shout Guards! Help! Help!");
    set_alarm(3.0, 0.0, "call_guards", enemy);
}

void
call_guards(object enemy)
{
    call_other(ENV(TO), "call_guards", enemy);
}

