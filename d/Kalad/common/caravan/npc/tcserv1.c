#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("servant");
    set_race_name("human");
    set_adj("servile");
    set_long("A skinny-looking individual that looks like he needs "+
      "several good meals. He is diligently cleaning his surroundings.\n");
    set_stats(({20, 30, 20, 20, 20, 15}));
    set_alignment(500);
    set_skill(SS_WEP_CLUB, 30);
    set_act_time(6);
    add_act("emote sweeps the floor.");
    add_act("emote wipes the sweat from his brow.");
    add_act(({"w", "say Ouch, I hate it when I forget about entering..."}));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_speak("The master expects every room to be clean.\n");
    set_knight_prestige(-5);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "tcsshirt")->move(TO);
    command("wear all");
    wep = clone_object(WEP + "tcsbroom")->move(TO);
    command("wield all");
    MONEY_MAKE_CC(random(10))->move(TO, 1);
}
