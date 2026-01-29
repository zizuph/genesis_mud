inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
int heal;
create_monster()
{
   int i;
   set_name("golem");
   add_name("statue");
   set_short("iron statue");
   set_race_name("golem");
   set_adj("iron");
   set_gender(G_NEUTER);
   set_long("A towering suit of iron mail armour. It stands nearly ten "+
      "feet in height and though the armour is very ornate, it still appears "+
      "to be of near mint condition. The statue must weigh an incredible "+
      "amount. You cannot be certain, but it seems as though a faint red glow "+
      "is emanating from beneath its helm.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 83 + random(50));
   set_base_stat(3, 25);
   set_base_stat(4, 25);
   set_base_stat(5, 100);
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
   add_prop(CONT_I_WEIGHT,2500000);
   add_prop(CONT_I_VOLUME,2500000);
   add_prop(LIVE_I_NO_CORPSE,1);
   trig_new("%w 'tries' 'to' 'go' 'south' %s","react_block");
}
int 
react_answer(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_answer",who);
      return 1;
   }
}
void
emote_hook(string emote, object actor, string adverb)
{
    if(emote == "hshow");
        set_alarm(3.0,0.0,"return_answer",actor);
}
void
return_answer(object obj)
{
   if(present(obj, environment()))
      {
      command("emote rumbles: You may pass.");
      obj -> move_living("south","/d/Kalad/common/wild/pass/drow/house7/chapel");
   }
}

int
react_block(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_block",who);
      return 1;
   }
}
void
return_block(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("emote suddenly animates and prepares to attack!\n");
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
   me = TO;
   attacktype = random(5);
   if (attacktype == 1)
      {
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 500 + random(250);
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
      me->heal_hp(1000);
      return 1;
   }
   
   return 0;
}
do_die(object killer)
{
   object corpse;
   if (query_hp() > 0) return;
   
   corpse = clone_object(CPASS(drow/obj/scrap));
   corpse->move(environment(TO));
   
   ::do_die(killer);
}
