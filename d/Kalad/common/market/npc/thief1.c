inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Dirty rotten thief , by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("ankaran");
    set_race_name("human");
    set_adj("thieving");
    add_adj("dirty");
    set_long(
     "This small guy is dressed in dirty, shabby clothes. He has a wicked\n"+
     "gleam to his eyes. He manuvers around these crowded market streets\n"+
     "with ease and skill. He is smiling slightly.....\n");
    set_stats(({40,45,30,25,30,15}));
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_PARRY,40);
    set_act_time(4);
    add_act("emote brushes againts you slightly.");
    add_act("emote eyes your purse with a greedy smile.");
    add_act("giggle misch");
    add_act("smile innocent");
    set_alarm(1.0, 0.0, "arm_me");
}
void
arm_me()
{
    object arm1,arm2,wep1;
    arm1 = clone_object("/d/Kalad/common/market/arm/thiefcloak.c");
    arm1 -> move(TO);
    arm2 = clone_object("/d/Kalad/common/market/arm/tleather.c");
    arm2 -> move(TO);
    wep1 = clone_object("/d/Kalad/common/market/wep/tdagger.c");
    wep1 -> move(TO);
    command("wear all");
    command("wield all");
    MAKE_MONEY_SC(random(20))->move(TO);
}

