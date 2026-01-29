/* 
 * /d/Kalad/common/wild/pass/npc/iron_golem.c
 * Purpose    : An iron golem that guards shadowgloom
 * Located    : /d/Kalad/common/wild/pass/underdark/u38
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
int heal;
create_monster()
{
   int i;
   set_name("golem");
   set_short("iron golem");
   set_race_name("golem");
   set_adj("iron");
   set_gender(G_NEUTER);
   set_long("A towering artificial construct, made entirely of magically "+
      "enchanted iron armour. The creature stands a full twelve feet in "+
      "height and must weigh an incredible amount. Two faintly glowing red "+
      "dots are visible in the dark cavity that serves as its eyes.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 150 + random(50));
   set_base_stat(3, 100);
   set_base_stat(4, 100);
   set_base_stat(5, 150);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,60);
   set_knight_prestige(1000);
   set_alignment(-1000);
   set_attack_unarmed(0, 50, 50, W_BLUDGEON, 30, "right iron gauntlet");
   set_attack_unarmed(1, 50, 50, W_BLUDGEON, 30, "left iron gauntlet");
   set_attack_unarmed(2, 45, 45, W_BLUDGEON, 20, "right iron boot");
   set_attack_unarmed(3, 45, 45, W_BLUDGEON, 20, "left iron boot");
   set_hitloc_unarmed(1, 75, 15, "iron helmet");
   set_hitloc_unarmed(2, 70, 10, "right gauntlet");
   set_hitloc_unarmed(3, 70, 10, "left gauntlet");
   set_hitloc_unarmed(4, 100, 45, "iron plate armour");
   set_hitloc_unarmed(5, 90, 20, "iron greaves");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME,3000000);
   add_prop(CONT_I_WEIGHT,3000000);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_act_time(3);
   add_act("get all");
   add_act("emote creaks as it shifts slightly.");
   add_act("emote stares directly at you with its glowing red eyes.");
}

void
emote_hook(string emote, object actor, string adverb)
{
   if (emote == "worship") set_alarm(1.0,0.0,"return_answer",actor);
}

void
return_answer(object who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("emote rumbles: You may pass.");
      obj -> move_living("west into the chamber of Shadowgloom","/d/Kalad/common/wild/pass/underdark/u37");
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
   me = TO;
   attacktype = random(5);
   if (attacktype == 1)
      {
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 600 + random(300);
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
         ob[i]->catch_msg("The iron golem's eyes flash a crimson red, and then "+
            "an acidic cloud emerges from its eyes directly at you!\n");
         ob[i]->catch_msg("You were " + how + " by the iron golem's acidic cloud!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the iron golem's acidic cloud!\n", ob[i]);
         
         
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
      write("The iron golem's eyes flash brightly!\n"+
         "The iron golem seems to have repaired some of the damage done to it!\n");
      say("The iron golem's eyes flash brightly!\n"+
         "The iron golem seems to have repaired some of the damage done to it!\n");
      me->heal_hp(1500);
      return 1;
   }
   
   return 0;
}
do_die(object killer)
{
   object corpse;
   if (query_hp() > 0) return;
   
   corpse = clone_object("/d/Kalad/common/wild/pass/obj/deadgolem");
   corpse->move(environment(TO));
   
   ::do_die(killer);
}
