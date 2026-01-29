/*
    ym_dinner_noble.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
    Updated with add_name ("human/man/nobleman") and removed second
     set_race_name and added set_pname("noblemen") Meton 2021
*/
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    string radj = ({"handsome", "tall", "young", "rich", "drunk", 
        "well-dressed"})[random(6)];
    object arm;

    set_name("noble");
    add_name("human");
    add_name("man");
    add_name("nobleman");
    set_pname("noblemen");
    set_race_name("human");
    set_adj(radj);
    set_short(radj +" noble");
    set_long("This is a fine, young nobleman. He looks like a real "+
        "party animal, but there is also an air of proudness to him. He "+
        "looks over you with a slight smile.\n");
    set_stats(({60,70,70,70,60,50}));
    set_skill(SS_DEFENCE,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY,40);
    set_alignment(400);
    set_knight_prestige(-100);

    set_act_time(5);
    add_act("emote wolfs down his food.");
    add_act("emote downs another glass of champagne.");
    add_act("emote toasts to the health of the rich.");
    add_act("laugh merr");
    add_act("say What a wonderful day to be alive!");
    add_act("emote cracks a joke about dwarves.");
    add_act("emote cracks a joke about goblins.");
    add_act("burp");
    add_act("emote laughs so hard that he spits out chunks of food.");
    add_act("emote whines about petty things.");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");
    add_cact("say Leave me alone! Waaa! Mommy!!");
    add_cact("cower");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    add_equipment(({
        NOBLE + "arm/e_leather_pants",
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/leather_shoes",
/*
        NOBLE + "arm/silver_pendant",
        NOBLE + "arm/ring",
*/
        NOBLE + "wep/jeweled_dagger",
        NOBLE + "arm/pierce1",
        }));

    arm = clone_object(NOBLE + "arm/single_ring");
    arm->set_ring_metal("gold");
    arm->set_ring_metal("onyx", 1);
    arm->set_ring_value(1872);
    arm->move(TO, 1);
    command("insert ring in left ear");
    
    // Wield when attacked
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

