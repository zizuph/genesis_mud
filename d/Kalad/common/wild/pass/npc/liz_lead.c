/* 
 * /d/Kalad/common/wild/pass/npc/liz_lead.c
 * Purpose    : A lizard leader
 * Located    : /d/Kalad/common/wild/pass/desert/salt/l*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   int i;
   set_name("lizard man leader");
   add_name("man");
   add_name("leader");
   set_race_name("lizard man");
   set_adj("brutal");
   set_short("brutal lizard man leader");
   set_pshort("brutal lizard man leaders");
   set_long("A large, reptilian humanoid that stands at just over six and "+
      "a half feet in height. Its glinting scaled skin barely covers the "+
      "incredibly muscled body underneath. Savage and intelligent slitted eyes "+
      "peer out at you suspiciously.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
   set_base_stat(i, 85 + random(25));
   set_base_stat(3, 55);
   set_base_stat(4, 55);
   set_base_stat(5, 80);
   set_all_hitloc_unarmed(15);
   set_alignment(-100);
   set_knight_prestige(400);
   set_skill(SS_WEP_POLEARM,80);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_BLIND_COMBAT,30);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,40);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("emote hisses.");
   add_act("grin men");
   add_act("snarl all");
   add_act("emote snaps up a passing fly.");
   add_act("emote licks the tip of its spear.");
   add_act("growl .");
   add_act("emote blinks its slitted eyes.");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("scream");
   add_cact("emote grins savagely.");
   add_cact("emote looks at you hungrily.");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/wep/lml_spear");
   it -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(12))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote hisses with absolute fury.");
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
      command("grin .");
   }
}
