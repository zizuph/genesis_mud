/* 
 * /d/Kalad/common/wild/pass/npc/g_scorpion.c
 * Purpose    : A giant scorpion
 * Located    : /d/Kalad/common/wild/pass/desert/rock
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_STING 3
#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3
#define H_TAIL 4
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("scorpion");
   set_race_name("scorpion");
   set_adj("giant");
   set_long("A massive-sized version of your common desert scorpion, "+
      "this particular species is nearly nine feet in length, not counting "+
      "its giant poisonous stinger, which seems to weave and bob before your "+
      "very eyes.\n");
   set_gender(G_NEUTER);
   set_stats(({70,60,80,5,5,60}));
   set_skill(SS_DEFENCE,50);
   set_random_move(10);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,50000);
   add_prop(CONT_I_VOLUME,50000);
   add_prop(OBJ_I_NO_INS, 1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   set_act_time(3);
   add_act("emote clacks its pincers together.");
   add_act("emote moves its stinger around.");
   add_act("emote crushes a small lizard with its stinger.");
   add_act("emote makes a strange sound.");
   add_act(({"kill human","kill elf","kill dwarf","kill gnome","kill hobbit","kill goblin"}));
   set_cact_time(3);
   add_cact("emote clacks its pincers together angrily.");
   add_cact("emote scurries towards you rapidly!");
   add_act("emote emits an odd sound.");
   set_attack_unarmed(A_BITE, 25, 25, W_IMPALE, 20, "fangs");
   set_attack_unarmed(A_LCLAW, 20, 20, W_SLASH, 30, "left pincer");
   set_attack_unarmed(A_RCLAW, 20, 20, W_SLASH, 30, "right pincer");
   set_attack_unarmed(A_STING, 30, 30, W_IMPALE, 20, "stinger");
   set_hitloc_unarmed(H_HEAD, ({ 30, 30, 30 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 40, 40, 40 }), 40, "body");
   set_hitloc_unarmed(H_ARMS, ({ 35, 35, 35 }), 15, "pincers");
   set_hitloc_unarmed(H_LEGS, ({ 25, 25, 25 }), 15, "legs");
   set_hitloc_unarmed(H_TAIL, ({ 30, 30, 30 }), 10, "stinger");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_STING)
      {
      tell_object(enemy,"The giant scorpion's stinger plunges into you!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(100);
         poison->set_strength(300);
         poison->set_damage(({POISON_FATIGUE, 300, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}
