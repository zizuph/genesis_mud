/* by Antharanos */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
int heal;
void
create_monster()
{
   int i;
   set_name("drow");
   add_name("wizard");
   set_race_name("drow");
   set_adj("merciless");
   set_short("drow wizard");
   set_long("An fear-inspiring drow dressed in the darkest of black "+
      "robes. His fearsome visage awakens in you nightmares in which "+
      "terrible demon-spawn arise from the bowels of the world to devour "+
      "all light and life...beginning with you.\n"+
      "He is wearing a midnight black robe.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(25));
   set_base_stat(3, 25);
   set_base_stat(4, 25);
   set_base_stat(5, 75);
   set_hp(query_max_hp());
   set_skill(SS_UNARM_COMBAT,75);
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_AWARENESS,90);
   set_skill(SS_SPELLCRAFT,80);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_alignment(-100);
   set_knight_prestige(800);
   set_act_time(3);
   add_act("smirk");
   add_act("grin menacingly all");
   add_act("cackle dem");
   add_act("snarl all");
   add_act("hide");
   add_act("say Wael!");
   
   add_prop(LIVE_I_SEE_DARK,10);
   set_alarm(1.0,0.0,"arm_me");
   trig_new("%w 'arrives.' %s","react_arrive");
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
      command("say Dos iblith! Usstan elgg dos!");
      command("kill " + lower_case(obj->query_real_name()));
   }
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/wild/pass/drow/arm/wizrobe");
   arm -> move(TO);
   command("wear all");
   MONEY_MAKE_PC(random(3))->move(TO,1);
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
         penet = 500 + random(250);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_COLD) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely frozen";
         if (hitresult[0] > 10)
            how = "slightly frozen";
         if (hitresult[0] > 20)
            how = "frozen quite badly";
         if (hitresult[0] > 40)
            how = "frozen very badly";
         if (hitresult[0] > 60)
            how = "utterly frozen";
         
         ob[i]->catch_msg("You hear a rhythmic chanting and then a deadly eruption "+
            "of frigid ice shoots forth from the wizard's hands at you!\n");
         ob[i]->catch_msg("You were " + how + " by the ice storm!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the ice storm!\n", ob[i]);
         
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
      write("The drow wizard incants several arcane words.\n"+
         "The drow wizard now looks much healthier!\n");
      say("The drow wizard incants several arcane words.\n"+
         "The drow wizard now looks much healthier!\n");
      me->heal_hp(1000);
      return 1;
   }
   return 0;
}
