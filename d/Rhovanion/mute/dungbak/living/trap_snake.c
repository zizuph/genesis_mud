inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <poison_types.h>
#define A_BITE  0
#define H_HEAD 0
#define H_BODY 1
#include <ss_types.h>
void
create_monster() {
   set_name("snake");
   set_adj("green");
   set_adj("small");
   set_race_name("snake");
   set_living_name("snake_lady");
   set_long("This looks like a very angry, very deadly small " +
      "snake.  It is an odd, brighter shade of green you haven't " +
      "seen often.  The snake has some vicious sharp fangs.\n");
   set_stats(({  5, 30, 20, 15, 15, 100 }));
   set_skill(SS_DEFENCE, 30);
   set_aggressive(1);
   set_alignment(-10);
   set_gender(G_NEUTER);
   set_hp(50);
   add_prop(LIVE_I_SEE_DARK, 5);
   add_prop(CONT_I_WEIGHT, 1000);
   add_prop(CONT_I_VOLUME,  900);
   set_attack_unarmed(A_BITE, 15, 10, W_IMPALE, 100, "dripping fangs");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15, 10 }), 15, "head");
   set_hitloc_unarmed(H_BODY, ({  5,  9, 10, 10 }), 85, "body");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      write("Your fangs bite deep!\n");
      tell_object(enemy, "The spider's fangs bite deep!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(100);
         poison->set_strength(40);
         poison->set_poison_type(POISON_HP);
         poison->set_damage(POISON_HP, 50);
         poison->start_poison();
      }
   }
   return 0;
}
