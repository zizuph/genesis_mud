inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by mhyrkhaan */

void
create_monster()
{
   ::create_monster();
   set_name("sreen");
   add_name("dark knight");
   set_race_name("guardian");
   set_adj("dark");
   add_adj("tall");
   set_long("The tall knight glares at you as you study him. "+
   "You can see your reflection in his smooth obsdian platemail. This "+
   "is definetly NOT someone you want to mess with.\n");
   set_stats(({150,150,150,150,150,200}));
   set_title("T'sarran, the Lord Protector and Master Knight of the Dark Realms");
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   set_act_time(20);
   add_act("say touch my master, and I will kill you.");
     set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    object wep, arm, arm2, arm3, arm4, arm5, arm6, arm7;
    seteuid(getuid(TO));
    wep = clone_object("/d/Kalad/mhyrkhaan/hob.c");
    wep -> move(TO);
    arm = clone_object("/d/Kalad/mhyrkhaan/private/plate.c");
    arm -> move(TO);
    arm2 = clone_object("/d/Kalad/mhyrkhaan/private/obshield.c");
    arm2 -> move(TO);
    arm3 = clone_object("/d/Kalad/mhyrkhaan/private/bcape.c");
    arm3 -> move(TO);
    arm4 = clone_object("/d/Kalad/mhyrkhaan/private/obgreaves.c");
    arm4 -> move(TO);
    arm5 = clone_object("/d/Kalad/mhyrkhaan/private/obgloves.c");
    arm5 -> move(TO);
    arm6 = clone_object("/d/Kalad/mhyrkhaan/private/shard.c");
    arm6 -> move(TO);
    arm7 = clone_object("/d/Kalad/mhyrkhaan/private/obboots.c");
    arm7 -> move(TO);
    command("wear all");
    command("wield all");
}
