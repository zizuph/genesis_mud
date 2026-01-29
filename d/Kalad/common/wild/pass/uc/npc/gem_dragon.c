inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_1 3
#define A_2 4
#define KILLED_GEM_DRAGON "_killed_gem_dragon"
object gemdrag;
/* by Antharanos */
int heal;
void
create_monster()
{
   int i;
   set_name("gelardyn");
   set_race_name("dragon");
   set_adj("sapphire");
   set_short("sapphire dragon");
   set_long("A truly glorious being, this dragon's coat is a deep ocean "+
      "blue in appearance, the individual scales appearing like nothing "+
      "more than the most valuable of sapphires, their myriad surfaces "+
      "reflecting the light in a dazzling array of beauty and majesty. "+
      "Coupled with this rare beauty is raw power, for the dragon is well "+
      "over ninety feet in length, possessed of massive, rippling muscles.\n");
   set_gender(G_NEUTER);
   for (i = 0; i < 3; i++)
   set_base_stat(i, 225 + random(50));
   set_base_stat(3, 175);
   set_base_stat(4, 150);
   set_base_stat(5, 250);
   set_aggressive(1);
   set_attack_chance(50);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,100);
   set_knight_prestige(1000);
   set_attack_unarmed(0, 100, 100, W_IMPALE, 24, "great fanged maw");
   set_attack_unarmed(1, 75, 75, W_BLUDGEON, 12, "enormous right wing");
   set_attack_unarmed(2, 75, 75, W_BLUDGEON, 12, "enormous left wing");
   set_attack_unarmed(A_1, 80, 80, W_SLASH, 16, "razor-sharp right claw");
   set_attack_unarmed(A_2, 80, 80, W_SLASH, 16, "razor-sharp left claw");
   set_attack_unarmed(5, 75, 100, W_BLUDGEON, 20, "gigantic tail");
   set_hitloc_unarmed(0, 100, 10, "massive horned head");
   set_hitloc_unarmed(1, 125, 40, "large sinuous body");
   set_hitloc_unarmed(2, 90, 20, "gigantic tail");
   set_hitloc_unarmed(3, 95, 20, "muscular legs");
   set_hitloc_unarmed(4, 50, 10, "great majestic wings");
   add_leftover("/d/Kalad/common/wild/pass/uc/obj/dragon_skin","skin",1,"",1,1);
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME,5500000);
   add_prop(CONT_I_WEIGHT,5500000);
   set_act_time(3);
   add_act("get all");
   add_act("get all from corpse");
   add_act(({"kill human","kill elf","kill dwarf","kill gnome","kill hobbit","kill goblin"}));
   trig_new("%w 'kicks' 'you' %s","react_attack");
   trig_new("%w 'attacks' 'you!\n' %s","react_attack");
   trig_new("%w 'arrives.\n' %s","react_attack");
   trig_new("%w 'starts' 'to' 'search' %s","react_attack");
   trig_new("%w 'touches' 'the' 'radiant' 'red' 'orb.\n' %s","react_touch");
   trig_new("%w 'uses' 'the' 'featureless' 'white' 'orb.\n' %s","react_death");
   set_alarm(2.0,0.0,"arrival");
}
int
react_touch(string who)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(1.0,0.0,"return_touch",who);
      return 1;
   }
}
void
return_touch(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment()))
      {
      command("touch orb");
      command("emote laughs cruelly.");
      command("say You will die for this affront, foolish mortal!");
      command("kill " + (obj->query_real_name()));
      set_alarm(2.0,0.0,"do_kill");
   }
}
int
react_death(string who)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_death",who);
      return 1;
   }
}
void
return_death(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("shout Death to you!");
      command("kill " + (obj->query_real_name()));
      obj -> add_prop(KILLED_GEM_DRAGON,1);
      set_alarm(3.0,0.0,"before_reaction");
   }
}
void
before_reaction()
{
   command("emote quivers as the orb's power begins to take affect.");
   set_alarm(10.0,0.0,"reaction");
}
void
reaction()
{
   command("emote is blasted into oblivion.");
   if(gemdrag = present("gelardyn",environment(TP)))
      {
      gemdrag -> remove_object();
   }
}
void
do_kill(string who)
{
   object obj;
   if(obj = present(who, environment()))
      {
      command("say Die worm!");
      command("kill " + (obj->query_real_name()));
   }
}
int
react_attack(string who, string dummy)
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
      command("snarl " + (obj->query_real_name()));
      command("kill " + (obj->query_real_name()));
   }
}
void
arrival()
{
   command("emote rumbles threateningly.");
   command("snarl human");
   command("kill human");
}
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   me = TO;
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
   attacktype = random(10);
   if (attacktype == 1)
      {
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 600 + random(600);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely shaken";
         if (hitresult[0] > 10)
            how = "slightly shaken";
         if (hitresult[0] > 20)
            how = "shaken quite badly";
         if (hitresult[0] > 40)
            how = "shaken very badly";
         if (hitresult[0] > 60)
            how = "completely overwhelmed";
         ob[i]->catch_msg("You hear a sharp intake of breath and then a "+
            "blast of pure sonic energy races from the sapphire dragon's mouth directly at you!\n");
         ob[i]->catch_msg("You were " + how + " by the dragon breath!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the dragon breath!\n", ob[i]);
         
         
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
      write("The sapphire dragon murmurs something unintelligible.\n");
      write("The sapphire dragon appears healthier!\n");
      say("The sapphire dragon murmurs something unintelligible.\n");
      say("The sapphire dragon appears healthier!\n");
      me->heal_hp(2000);
      return 1;
   }
   
   return 0;
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_1)
      {
      tell_object(enemy,"A hail of magic missiles strikes you!\n");
      say("A hail of magic missiles strikes " + QTNAME(enemy) + " in the chest!\n");
      {
         enemy -> heal_hp(-250);
         enemy -> command("scream");
      }
   }
   if(aid == A_2)
      {
      tell_object(enemy,"A beam of green energy leaps from the sapphire dragon "+
         "and strikes you in the head!\n");
      say("A beam of green energy leaps from the sapphire dragon "+
         "and strikes " + QTNAME(enemy) + " in the head!\n");
      {
         enemy -> add_mana(-250);
         tell_object(enemy, "You clutch your head in pain!\n");
         say(QCTNAME(enemy) + " clutches " + enemy->query_possessive() + " head in pain.\n");
      }
   }
   return 0;
}
