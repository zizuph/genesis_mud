/* 
 * /d/Kalad/common/wild/pass/npc/rt_sandling.c
 * Purpose    : A sandling creature
 * Located    : /d/Kalad/common/wild/pass/desert/sand/
 * Created By : ANtharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   int i;
   set_name("sandling");
   set_race_name("sandling");
   set_adj("aggressive");
   set_long("For the life of you, this strange thing looks to be "+
      "nothing more than a vaguely humanoid-shaped mound of sand...a "+
      "moving mound of sand that rises to ten feet in height.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
   set_base_stat(i, 50 + random(50));
   set_base_stat(3, 25);
   set_base_stat(4, 25);
   set_base_stat(5, 75);
   set_aggressive(1);
   set_all_hitloc_unarmed(25);
   set_skill(SS_UNARM_COMBAT,75);
   set_skill(SS_BLIND_COMBAT,75);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("emote shifts slightly.");
   add_act("emote moves silently across the sand.");
   add_act("emote suddenly sprouts an appendage.");
   set_cact_time(3);
   add_cact("emote is strangely quiet.");
   add_prop(LIVE_I_SEE_DARK,1);
   trig_new("%w 'drops' %s","react_drop");
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote rapidly shifts around.");
      command("kill " + (ob->query_real_name()));
   }
}
int
react_drop(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("get all");
   }
}
