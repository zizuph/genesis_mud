inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include <poison_types.h>
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LWING 1
#define A_RWING 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WINGS 3
/* by Antharanos */
create_monster() {
   set_name("spider");
   set_race_name("spider");
   set_adj("hunting");
   set_long("A gigantic arachnid, measuring as much as ten feet across "+
      "when including the legs. That however is not the most amazing thing "+
      "about it, for spouting upon its back are two gossamer wings!\n");
   set_gender(G_NEUTER);
   set_stats(({55,55,55,30,30,80}));
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,60);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,50000);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_act_time(3);
   add_act("emote clacks its mandibles together.");
   add_act("emote flaps its wings ever so slightly.");
   add_act("emote leaps into the air and circles you from above.");
   set_attack_unarmed(A_BITE, 25, 15, W_IMPALE, 10, "mandibles");
   set_attack_unarmed(A_LWING, 20, 15, W_BLUDGEON, 45, "left wing");
   set_attack_unarmed(A_RWING, 20, 15, W_BLUDGEON, 45, "right wing");
   set_hitloc_unarmed(H_HEAD, ({ 10, 10, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 15 }), 40, "body");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
   set_hitloc_unarmed(H_WINGS, ({ 5, 5, 5 }), 20, "wings");
   add_prop(LIVE_I_SEE_DARK,10);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy, "The spider swoops down and clamps its mandibles into you!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(200);
         poison->set_strength(50);
         poison->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}
