#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("thug");
    set_race_name("human");
    set_adj("brutal");
    set_short("brutal thug");
    set_long("A brutal-looking human being! He looks at you with such "+
      "hatred and malice in his heart that you almost feel pity for such a "+
      "wretched soul, almost that is, if he weren't about to kill you!\n");
    set_stats(({75, 80, 75, 50, 50, 60}));
    set_aggressive(1);
    set_alignment(-250);
    set_skill(SS_WEP_KNIFE, 70);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 60);
    set_act_time(9);
    add_act("laugh evilly");
    add_act("say I'm going to cut your throat out!");
    add_act("say I'll enjoy looting your corpse!");
    add_act("get all from corpse");
    set_cact_time(9);
    add_cact("say I love senseless acts of violence!");
    add_cact("say The guards will never know I killed you!");
    add_speak("I'm gonna kill ya!\n");
    set_knight_prestige(250);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep = clone_object(WEP + "thugdag");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_SC(random(20))->move(TO, 1);
}
