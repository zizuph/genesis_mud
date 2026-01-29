/* by Antharanos */
#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <poison_types.h>

#define A_BITE  0
#define A_LP 1
#define A_RP 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

create_creature()
{
   set_name("arachnid");
   add_name("spider");
   set_race_name("spider");
   set_adj("large");
   add_adj("black");
   set_long("A large spider of the color of night, it measures just over "+
      "a foot across. The red hourglass symbol on its abdomen indicates "+
      "it as a black widow spider, favored spider of Lolth.\n");
   
   set_stats(({10,15,10,5,5,15}));
   
   set_gender(G_NEUTER);
   
   set_skill(SS_DEFENCE,10);
   
   set_attack_unarmed(A_BITE, 15, 15, W_IMPALE, 30, "needle-sharp fangs");
   set_attack_unarmed(A_LP, 10, 10, W_IMPALE, 35, "left pincer");
   set_attack_unarmed(A_RP, 10, 10, W_IMPALE, 35, "right pincer");
   
   set_hitloc_unarmed(H_HEAD, ({ 10, 20, 20 }), 20, "black head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 30 }), 70, "round body");
   set_hitloc_unarmed(H_LEGS, ({ 5, 10, 10 }), 10, "spindly legs");
   
   set_random_move(10);
   set_act_time(6);
   
   add_act("emote clacks its fangs together.");
   add_act("emote gazes at you with its multitude of eyes.");
   
   add_prop(OBJ_I_WEIGHT,300);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(CONT_I_WEIGHT,300);
   add_prop(CONT_I_VOLUME,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   
   remove_prop(OBJ_I_NO_GET);
   
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy, "The large black spider's needle-sharp fangs bite into you!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(100);
         poison->set_strength(100);
         poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}
