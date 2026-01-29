inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Shark's mean bodyguard, by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("brute");
    set_race_name("human");
    set_adj("hulking");
    add_adj("mean");
    set_long(
     "This is a mean looking human. He his very large for a human, and as\n"+
     "you study him further, you start to think that he is not all human,\n"+
     "and perhaps ogre blood runs in his veins. Either way, you don't want\n"+
     "to mess with him.\n");
   set_stats(({180,80,200,40,30,120}));
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,60);
   set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object arm1,wep1,arm2;
    arm1 = clone_object("/d/Kalad/common/market/arm/bsleather");
    arm1 -> move(TO);
    arm2 = clone_object("/d/Kalad/common/market/arm/bsleatherg");
    arm2 -> move(TO);
    command("wear all");
    wep1 = clone_object("/d/Kalad/common/market/wep/bwclub");
    wep1 -> move(TO);
    command("wield all");
}

