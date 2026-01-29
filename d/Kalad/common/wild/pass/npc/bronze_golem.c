/* 
 * /d/Kalad/common/wild/pass/npc/bronze_golem.c
 * Purpose    : The golem that holds a tablet for the tablet quest
 * Located    : /d/Kalad/common/wild/pass/underdark/u37a
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
int heal;
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("golem");
   add_name("bronze golem");
   set_race_name("golem");
   set_adj("bronze");
   set_gender(G_NEUTER);
   set_short("bronze golem");
   set_long("A towering artificial construct, made entirely of magically "+
      "enchanted bronze armour. The creature stands at roughly eight feet in "+
      "height and must weigh an incredible amount. Two faintly glowing red "+
      "dots are visible in the dark cavity that serves as its eyes.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 125 + random(25));
   set_base_stat(3, 100);
   set_base_stat(4, 100);
   set_base_stat(5, 125);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,60);
   set_knight_prestige(1000);
   set_attack_unarmed(0, 45, 45, W_BLUDGEON, 30, "right bronze gauntlet");
   set_attack_unarmed(1, 45, 45, W_BLUDGEON, 30, "left bronze gauntlet");
   set_attack_unarmed(2, 40, 40, W_BLUDGEON, 20, "right bronze boot");
   set_attack_unarmed(3, 40, 40, W_BLUDGEON, 20, "left bronze boot");
   set_hitloc_unarmed(1, 70, 15, "bronze helmet");
   set_hitloc_unarmed(2, 65, 10, "right gauntlet");
   set_hitloc_unarmed(3, 65, 10, "left gauntlet");
   set_hitloc_unarmed(4, 90, 45, "bronze plate armour");
   set_hitloc_unarmed(5, 85, 20, "bronze greaves");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME,2000000);
   add_prop(CONT_I_WEIGHT,2000000);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_act_time(3);
   add_act("get all");
   add_act("emote creaks as it shifts slightly.");
   add_act("emote stares directly at you with its glowing red eyes.");
   trig_new("%w 'falls' 'on' %s", "react_answer");
   trig_new("%w 'arrives.' %s", "react_arrive");
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object item;
   item = clone_object("/d/Kalad/common/wild/pass/obj/tablet");
   item -> move(TO);
}
int 
react_answer(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_answer",who);
      return 1;
   }
}
void
return_answer(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("emote rumbles...you realize it is laughing at you.");
   }
}
int
react_arrive(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("emote intones: You have proven yourself both intelligent and resourceful, as well as powerful, to have reached this far. Now, you " + obj->query_real_name() + ", must face your final test...\n");
      command("kill " + (obj->query_real_name()));
   }
}
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}
int
special_attack(object enemy)
{
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;
   me = this_object();
   attacktype = random(5);
   if (attacktype == 1)
      {
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 500 + random(100);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely burned";
         if (hitresult[0] > 10)
            how = "slightly burned";
         if (hitresult[0] > 20)
            how = "burned quite badly";
         if (hitresult[0] > 40)
            how = "burned very badly";
         if (hitresult[0] > 60)
            how = "utterly devastated";
         ob[i]->catch_msg("The bronze golem's eyes flash a crimson red, and then "+
            "an acidic cloud emerges from its eyes directly at you!\n");
         ob[i]->catch_msg("You were " + how + " by the bronze golem's acidic cloud!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the bronze golem's acidic cloud!\n", ob[i]);
         
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
       }
      return 1;
   }
   
   if (attacktype == 2)
      {
      if (heal == 5)
         {
         return 0;
       }
      heal += 1;
      write("The bronze golem's eyes flash brightly!\n"+
         "The bronze golem seems to have repaired some of the damage done to it!\n");
      say("The bronze golem's eyes flash brightly!\n"+
         "The bronze golem seems to have repaired some of the damage done to it!\n");
      me->heal_hp(750);
      return 1;
   }
   
   return 0;
}
do_die(object killer)
{
   object corpse;
   if (query_hp() > 0) return;
   
   corpse = clone_object("/d/Kalad/common/wild/pass/obj/deadgolem1");
   corpse->move(environment(TO));
   
   ::do_die(killer);
}
