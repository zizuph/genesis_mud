/* 
 * /d/Kalad/common/wild/pass/npc/rt_gzombie.c
 * Purpose    : A zombie
 * Located    : /d/Kalad/common/wild/pass/desert/sand/r*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("zombie");
   set_race_name("zombie");
   set_adj("giant");
   set_long("The hulking, animated remains of a giant. The undead creature "+
      "stands at an alarmingly tall sixteen feet in height. An almost "+
      "overwhelming smell of rotten flesh emanates from it.\n");
   set_stats(({100,75,100,1,1,100}));
   set_knight_prestige(500);
   set_aggressive(1);
   set_skill(SS_WEP_CLUB,50);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,25);
   set_skill(SS_AWARENESS,50);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_UNDEAD,25);
   add_prop(CONT_I_WEIGHT,500000);
   add_prop(CONT_I_VOLUME,500000);
   set_act_time(6);
   add_act("moan");
   add_act("groan");
   set_cact_time(6);
   add_cact("moan");
   add_cact("groan");
}
void
arm_me()
{
   object wep;
   seteuid(getuid(TO));
   wep = clone_object(CPASS(wep/rt_gzclub));
   wep -> move(TO);
   command("wield all");
}
