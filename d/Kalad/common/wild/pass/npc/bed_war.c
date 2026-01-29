/* 
 * /d/Kalad/common/wild/pass/npc/bed_war.c
 * Purpose    : A bedellin warrior
 * Located    : /d/Kalad/common/wild/pass/desert/camp/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(3);
   if(i < 1)
      return "/d/Kalad/common/wild/pass/wep/bed_dag";
   else if (i < 2)
      return "/d/Kalad/common/wild/pass/wep/bed_sword";
   else
      return "/d/Kalad/common/wild/pass/wep/bed_spear";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("nomad");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin nomad");
   set_long("A dark-haired and dark-skinned man, his features wrinkled "+
      "from constant exposure to the Kaladian sun and biting winds of the "+
      "desert known as the Great Kalad Waste. His constantly-moving eyes "+
      "indicate someone learned in the ways of the desert.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 60 + random(30));
   set_base_stat(3, 60);
   set_base_stat(4, 60);
   set_base_stat(5, 65);
   set_alignment(600);
   set_knight_prestige(-3);
   set_random_move(10);
   set_skill(SS_WEP_KNIFE,70);
   set_skill(SS_WEP_POLEARM,80);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,70);
   set_act_time(6);
   add_act("hmm");
   add_act("say A great dust storm is coming from the north.");
   add_act("emote scans the area, eyes alert to danger.");
   add_act("say It looks like T'har shall feast well tonight.");
   set_cact_time(6);
   add_cact("say Die infidel!");
   add_cact("say May T'har swallow you whole!");
   add_cact("say Esh el-kalam da?!?");
   add_cact("emote grimaces.");
   add_speak("The Great Kalad Waste is the only world there is.\n");
   trig_new("%w 'spits' %s","react_spit");
}
void
my_stuff()
{
   object item;
   int i;
   string extra;
   extra = random_extra();
   seteuid(getuid(TO));
   item = clone_object(extra);
   item -> move(TO);
   command("wield all");
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_robe");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_keff");
   item -> move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(20))->move(TO,1);
}
int
react_spit(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_spit",who);
      return 1;
   }
}
void
return_spit(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("say That is a waste of body liquids.");
      command("say A word of advice, save your spit.");
   }
}
