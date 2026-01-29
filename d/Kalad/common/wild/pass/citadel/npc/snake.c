inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include <poison_types.h>
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
/* by Korat ... a death trap snake */
create_monster() {
   set_name("snake");
   set_race_name("snake");
   set_adj("venomous");
   set_long("A slim snake coiling its body up like the string on "+
      "a bow, ready to strike out with its deadly fangs.\n");
   set_gender(G_NEUTER);
   set_stats(({80,80,60,30,30,100}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_attack_unarmed(A_BITE, 60, 30, W_IMPALE, 100, "fangs");
   set_hitloc_unarmed(H_HEAD, ({ 10, 10, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 20, 20, 20 }), 80, "body");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_SEE_INVIS,1);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy, "The snake strikes out and clamps its fangs into you!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(2000);
         poison->set_interval(50);
         poison->set_strength(80);
         poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}
