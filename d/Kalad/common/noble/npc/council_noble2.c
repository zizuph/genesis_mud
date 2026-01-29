/*
    council_noble2.c
    
    Code by Sarr,
    Recoded by Fysix, Feb 1998
 */
/* 2017-06-04 Malus: Added race name */ 
inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    object arm, wep;
    
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
    set_alignment(random(600));
    set_knight_prestige(-random(300));

    set_act_time(5);
    add_act("shout The Red Fang are a real threat to Kabal! We must "+
      "heed their warnings, and must try to negotiate with them. Our "+
      "militia has had no luck thus far!");
    add_act("say We cannot disregard the Shadow Walkers...else we "+
      "must face a darker threat!");
    add_act("scratch behind");
    add_act("boggle");
    add_act("The trade is prosperous and has brought great wealth to "+
      "Kabal, but we must expand even further!");
    add_act("The peasants are beginning to get restless...we must appease "+
      "them somehow!");

    set_cact_time(3);
    add_cact("shout Help ! Help !");
    add_cact("say What did I ever do to you!");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    arm = clone_object(CVAN + "arm/skrobe");
    arm->move(TO, 1);
    arm->set_long("This robe is used by the council members of the "+
      "High Council. It is finely woven, with the insignia of the "+
      "High Lord on shoulder.\n");
    arm->move(TO);
    command("wear all");

    // Wield when attacked    
    wep = clone_object(NOBLE + "wep/silver_dagger");
    wep->move(TO, 1);
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    command("wield all");
    command("shout Guards! Help! Help!");
    set_alarm(3.0,0.0,"call_guards",enemy);
}

void
call_guards(object enemy)
{
    call_other(ENV(TO),"call_guards",enemy);
}

