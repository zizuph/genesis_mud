#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("egore");
    set_race_name("human");
    set_adj("merciless");
    set_long("A balding, chubby individual that peers around as if he "+
      "owned everything here, including the people. Perhaps it is because "+
      "he does own the people here! At least the slaves, that is.\n");
    set_stats(({80, 60, 75, 50, 50, 60}));
    set_alignment(-750);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_2H_COMBAT, 50);
    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 50);
    set_act_time(6);
    add_act("smirk");
    add_act("snarl");
    add_act("shout Keep it moving you miserable curs!");
    add_act("spit slave");
    add_act("kick slave");
    add_act("crack");
    set_cact_time(3);
    add_cact("grin mer all");
    add_cact("say I'll beat you just like I do my slaves.");
    set_title("the Slave Overseer");
    add_speak("Whadda you want?!?\n");
    set_knight_prestige(750);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));
    arm = clone_object(ARM + "sovest");
    arm->move(this_object());
    arm = clone_object(ARM + "sogloves");
    arm->move(this_object());
    arm = clone_object(ARM + "soboots");
    arm->move(this_object());
    arm = clone_object(OBJ + "ikey");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "soclub");
    wep->move(this_object());
    wep = clone_object(WEP + "sowhip");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_SC(random(30))->move(this_object(), 1);
}
