#pragma strict_types

inherit "/d/Cirath/std/monster.c";
#include "../defs.h"

void
create_monster()
{
    ::create_monster();
    set_name("guard");
    add_name("wguard");
    set_race_name("mul");
    set_adj("big");
    add_adj("burly");
    set_gender(0);
    set_long("This mul is selling water skins." +
        " He looks wery dangerous.\n");
        
    add_prop (LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);

    set_act_time(7);
    add_act("emote eyes you up and down.");
    add_act("emote leans against the well.");
    add_act("emote crosses his arms on his chest.");
    add_act("say Want water? Then pay for it!");
    add_act("grin wickedly");
    add_act("say grabs a waterskin and pours it on his head.");
    add_act("say Don't even think about it!.");
    set_cact_time(5);
    add_cact("shout Guards!!");
    add_cact("emote lunges at you with a deft maneuver.");
    add_cact("emote tries to sweep your feet from under you.");
    add_cact("say Don't let 'em get away!");
    add_cact("say Now you die.");

   set_alignment(-400);
    set_assist_cry("Now you die!");
    set_stats(({135, 130, 160, 60, 65, 120}));

    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENCE,  70);
    set_skill(SS_PARRY, 50);
}

void
arm_me()
{
    clone_object(ALT_WEP + "obs_mace")->move(TO);
    command("wield all");
    clone_object(ALT_ARM + "m_mail_tmp")->move(TO);
    clone_object(ALT_ARM + "bracers_tmp")->move(TO);
    make_cash((random(5)+5), "copper");
    command("wear all");
}


