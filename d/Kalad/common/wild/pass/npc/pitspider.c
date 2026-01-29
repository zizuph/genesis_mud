/* 
 * /d/Kalad/common/wild/pass/npc/pitspider.c
 * Purpose    : A poisonous spider
 * Located    : /d/Kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#define A_BITE 0
#define A_LPINCER 1
#define A_RPINCER 2
#define H_BODY 0
/* by Antharanos */
create_monster() {
   set_name("spider");
   set_race_name("spider");
   set_adj("pit");
   set_long("An extremely large arachnid sporting vicous-looking mandibles, "+
      "which veritably drip with poison. It displays two razor-sharp pincers "+
      "that look easily capable of ripping you apart, limb from limb.\n");
   set_gender(G_NEUTER);
   set_stats(({75,75,75,50,50,100}));
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,50);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_I_WEIGHT, 4500);
   add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_random_move(10);
   set_act_time(3);
   add_act("emote clacks its mandibles together.");
   add_act("emote removes a chunk of flesh from its mandibles.");
   set_attack_unarmed(A_BITE, 20, 10, W_IMPALE, 30, "mandibles");
   set_attack_unarmed(A_LPINCER, 25, 20, W_IMPALE, 35, "left pincer");
   set_attack_unarmed(A_RPINCER, 25, 20, W_IMPALE, 35, "right pincer");
   set_hitloc_unarmed(H_BODY, ({  15, 15, 10 }), 100, "body");
   add_prop(LIVE_I_SEE_DARK,10);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy, "The spider's mandibles clamp into your torso!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(100);
         poison->set_strength(100);
         poison->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}
