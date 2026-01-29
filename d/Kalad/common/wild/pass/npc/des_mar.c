/* 
 * /d/Kalad/common/wild/pass/npc/des_mar.c
 * Purpose    : The desert marauder of the WASTE
 * Located    : It must be killed for a quest
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";

#include "/d/Kalad/defs.h"

#define KILLED_DES_MAR "_killed_des_mar"
#define A_LARM 1
#define A_RARM 2
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_TAIL 4

object killer;

/* The Desert Marauder, the gigantic larval being from which all other
marauders come from. It is a unique individual. */
/* by Antharanos */
create_monster()
{
   set_name("bigdaddymarauder");
   set_race_name("marauder");
   set_adj("great");
   add_adj("desert");
   set_long("A great mass of wrinkled, grey flesh measuring well over "+
      "fifty feet in length and half that in width. In what can reasonably "+
      "be discerned as the creature's head lies a gaping maw filled with "+
      "numerous spike-shaped teeth. Two appendages vaguely similar to arms "+
      "sprout from the sides of the beast, completing the grotesque image "+
      "of the thing.\n");
   set_stats(({300,200,400,75,75,300}));
   set_gender(G_NEUTER);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_attack_unarmed(A_MOUTH, 90, 90, W_IMPALE, 20, "gigantic spike-filled mouth");
   set_attack_unarmed(A_LARM, 75, 75, W_BLUDGEON, 40, "massive left appendage");
   set_attack_unarmed(A_RARM, 75, 75, W_BLUDGEON, 40, "massive right appendage");
   set_hitloc_unarmed(H_HEAD, ({ 80, 80, 80 }), 25, "enormous wrinkled head");
   set_hitloc_unarmed(H_BODY, ({ 120, 120, 120 }), 45, "ponderous body");
   set_hitloc_unarmed(H_LARM, ({ 100, 100, 100 }), 10, "gangly left arm");
   set_hitloc_unarmed(H_RARM, ({ 100, 100, 100 }), 10, "gangly right arm");
   set_hitloc_unarmed(H_TAIL, ({ 100, 100, 100 }), 10, "long, wrinkled tail");
   set_act_time(3);
   add_act("emote twists the spike-shaped teeth in its mouth.");
   add_act("emote moves, its flesh rippling strangely.");
   set_cact_time(3);
   add_cact("emote shifts its massive bulk in your direction.");
   set_random_move(10);
   set_aggressive(1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,5000000);
   add_prop(CONT_I_VOLUME,5000000);
   add_prop(OBJ_I_RES_MAGIC,100);
   trig_new("%w 'uses' 'the' 'mara' 'rune.\n' %s","react_rune");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_MOUTH)
      {
      tell_object(enemy,"The great desert marauder's giant spike-filled mouth tears into you!\n");
      {
         enemy -> add_mana(-500);
         if(enemy->query_mana() <= 0)
            {
            enemy -> command("$options wimpy brave");
         }
      }
   }
   return 0;
}
int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(750 + random(250), W_BLUDGEON, me, -1);
   how = " with a glancing blow";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 10)
      how = " hard";
   if (hitresult[0] > 20)
      how = " very hard";
   if (hitresult[0] > 30)
      how = " extremely hard";
   if (hitresult[0] > 40)
      how = " tremendously hard";
   me -> catch_msg("You attempt to crush your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is struck"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to crush you with its ponderous bulk!\n"+
      "You are struck" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to crush " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is struck"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
int
react_rune(string who, string dummy)
{
   if(who)
   {
      if(!objectp(killer) && objectp(killer = find_player(lower_case(who))))
      {
         killer->add_prop(KILLED_DES_MAR, 1);
      }
      set_alarm(4.0, 0.0, "return_rune");
      return 1;
   }
}
void
return_rune()
{
   command("emote cringes violently in fear and pain.");
   set_alarm(2.0,0.0, "reaction");
}
void
reaction()
{
   command("emote shrivels into dust and is blown away by the wind.");
   remove_object();
}
