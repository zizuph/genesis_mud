inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
#define A_F1 1
#define A_F2 2
create_monster()
{
   int i;
   set_name("hound");
   set_adj("terrible");
   add_adj("hell");
   set_race_name("hound");
   set_gender(G_NEUTER);
   set_long("A large, rothe-sized beast the color of dried blood. Its "+
      "form is completely hairless, leaving its dark leathery hide exposed. "+
      "Its disgusting head is as hairless as the rest of its body, "+
      "and sports a large maw filled with rows upon rows of needle-sharp "+
      "teeth. Most horrifying of all are its eyes, for it has none. From "+
      "within its eyeless sockets emanates a black aura, one that promises "+
      "death to any that oppose it.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(50));
   set_base_stat(3, 25);
   set_base_stat(4, 25);
   set_base_stat(5, 100);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_knight_prestige(1000);
   set_alignment(-1000);
   set_attack_unarmed(0, 50, 50, W_IMPALE, 80, "tremendous maw");
   set_attack_unarmed(A_F1, 60, 60, W_BLUDGEON, 10, "left paw");
   set_attack_unarmed(A_F2, 60, 60, W_BLUDGEON, 10, "right paw");
   set_hitloc_unarmed(1, 50, 15, "gnarled head");
   set_hitloc_unarmed(2, 40, 10, "right front leg");
   set_hitloc_unarmed(3, 40, 10, "left front leg");
   set_hitloc_unarmed(4, 60, 45, "gnarled body");
   set_hitloc_unarmed(5, 40, 20, "rear legs");
   set_act_time(6);
   add_act("snarl all");
   add_act("emote paces around the room.");
   add_act("emote seems to stare at you with its eyeless sockets.");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_WEIGHT,500000);
   add_prop(CONT_I_VOLUME,500000);
   add_prop(LIVE_I_NEVERKNOWN,1);
   trig_new("%w 'proudly' 'shows' 'the' 'insignia' 'of' 'House' 'Noquar.\n' %s","react_answer");
   trig_new("%w 'proudly' 'shows' 'the' 'insignia' 'of' 'House' 'Claddath.\n' %s","react_attack");
   trig_new("%w 'proudly' 'shows' 'the' 'insignia' 'of' 'House' 'Kilsek.\n' %s","react_attack");
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
return_answer(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("growl");
      command("nod " + (obj->query_real_name()));
      obj -> move_living("east","/d/Kalad/common/wild/pass/drow/house8/mm_chamber");
   }
}
int
react_attack(string who)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("growl " + (obj->query_real_name()));
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
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
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
         ob[i]->catch_msg("The terrible hell hound spews forth a tremendous "+
            "blast of fire that blankets the room!\n");
         ob[i]->catch_msg("You were " +how+ " by the blanket of fire!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the blanket of fire!\n", ob[i]);
         
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
       }
      return 1;
   }
   
   return 0;
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_F1)
      {
      tell_object(enemy,"Globs of molten fire explode from the terrible hell "+
         "hounds maw and directly at you!\n");
      tell_object(enemy,"You are struck by the globs of molten fire!\n");
      {
         enemy -> heal_hp(-250);
      }
   }
   if(aid == A_F2)
      {
      tell_object(enemy,"A hail of small fireballs explodes towards you!\n");
      tell_object(enemy,"You are hit by several of them!\n");
      {
         enemy -> heal_hp(-125);
      }
   }
   return 0;
}
