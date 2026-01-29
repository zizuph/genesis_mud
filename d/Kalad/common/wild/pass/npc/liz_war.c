/* 
 * /d/Kalad/common/wild/pass/npc/liz_war.c
 * Purpose    : A lizard man war leader
 * Located    : /d/Kalad/comon/wild/pass/desert/salt/l*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   int i;
   set_name("lizard man war leader");
   add_name("man");
   add_name("leader");
   add_name("war leader");
   set_race_name("lizard man");
   set_adj("merciless");
   set_short("merciless lizard man war leader");
   set_pshort("merciless lizard man war leaders");
   set_long("A large, reptilian humanoid that stands nearly seven feet "+
      "in height. Its greenish-scaled skin covers a muscular frame, while "+
      "its savage, slitted eyes peer at you with their unblinking gaze.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(25));
   set_base_stat(3, 60);
   set_base_stat(4, 60);
   set_base_stat(5, 85);
   set_all_hitloc_unarmed(20);
   set_alignment(-100);
   set_knight_prestige(600);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_BLIND_COMBAT,40);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,70);
   set_act_time(6);
   add_act("emote hisses.");
   add_act("grin men");
   add_act("snarl all");
   add_act("emote snaps up a passing fly.");
   add_act("emote licks the tip of its spear.");
   add_act("peer");
   add_act("scratch chin");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("scream");
   add_cact("emote grins savagely.");
   add_cact("cackle");
   add_cact("startle all");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
   trig_new("%w 'wears' %s","react_wear");
}
void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/wep/lmwl_spear");
   it -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(20))->move(TO,1);
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
      command("cackle");
   }
}
int
react_wear(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_wear",who);
      return 1;
   }
}
void
return_wear(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("point " + (obj->query_real_name()));
      command("emote hisses something incomprehensible.");
      command("kill " + (obj->query_real_name()));
   }
}
