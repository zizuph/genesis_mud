/* 
 * /d/Kalad/common/wild/pass/npc/tfemale.c
 * Purpose    : A female troglodyte
 * Located    : /d/Kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("female");
   set_race_name("troglodyte");
   set_adj("female");
   set_short("troglodyte female");
   set_long("A reptilian humanoid that stands roughly five and a half feet in "+
      "height and is completely covered in glistening, leathery scales. "+
      "A toothless lizard-like head completes the gross picture.\n");
   set_gender(G_FEMALE);
   set_stats(({50,45,50,30,30,55}));
   set_alignment(-25);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,40);
   set_act_time(6);
   add_act("growl all");
   add_act("glare all");
   add_act("rsay Fresh meat for hatchling!");
   set_cact_time(3);
   add_cact("emote looks like she wants to feed you to a hatchling.");
   add_cact("rsay Me and hatchling eat you!");
   set_knight_prestige(25);
   add_prop(LIVE_I_SEE_DARK,10);
   MONEY_MAKE_CC(random(50))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("rsay I feed " + ob->query_race_name() + " to hatchling!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
