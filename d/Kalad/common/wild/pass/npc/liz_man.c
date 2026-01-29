/* 
 * /d/Kalad/common/wild/pass/npc/liz_man.c
 * Purpose    : A lizard man
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
   set_name("lizard man");
   add_name("man");
   set_race_name("lizard man");
   set_adj("feral");
   set_short("feral lizard man");
   set_pshort("feral lizard men");
   set_long("A large, reptilian humanoid that stands at roughly six and a "+
      "half feet in height. Its scaled skin is colored both tawny and "+
      "green at the same time, and the slitted eyes protruding from its "+
      "lizard-like head are the stuff of nightmares.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(25));
   set_base_stat(3, 50);
   set_base_stat(4, 50);
   set_base_stat(5, 75);
   set_all_hitloc_unarmed(10);
   set_alignment(-100);
   set_knight_prestige(200);
   set_skill(SS_WEP_POLEARM,70);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_BLIND_COMBAT,30);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,30);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("emote hisses.");
   add_act("grin men");
   add_act("snarl all");
   add_act("emote snaps up a passing fly.");
   add_act("emote licks the tip of its spear.");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("scream");
   add_cact("emote grins savagely.");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/wep/lm_spear");
   it -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(10))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote hisses angrily!");
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
      command("emote hisses with delight.");
   }
}
