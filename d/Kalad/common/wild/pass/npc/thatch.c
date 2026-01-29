/* 
 * /d/Kalad/common/wild/pass/npc/thatch.c
 * Purpose    : A troglodyte hatchling
 * Located    : /d/kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("hatchling");
   add_name("infant");
   set_race_name("troglodyte");
   set_adj("infant");
   set_short("troglodyte hatchling");
   set_long("A small reptilian humanoid, standing a mere three feet in "+
      "height and covered in soft, leathery scales. Its small head looks "+
      "for the most part human, not considering the leathery scales, yet is "+
      "already beginning to appear like a lizard's face.\n");
   set_stats(({25,20,25,15,15,25}));
   set_alignment(-5);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_AWARENESS,40);
   set_act_time(6);
   add_act("growl all");
   add_act("glare all");
   add_act("emote snatches up a bug on the floor and pops it into its mouth.");
   set_cact_time(3);
   add_cact("emote looks at you as if you were dinner.");
   add_cact("rsay Food!");
   set_knight_prestige(5);
   add_prop(LIVE_I_SEE_DARK,10);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("rsay Me eat " + ob->query_race_name() + " for food!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
