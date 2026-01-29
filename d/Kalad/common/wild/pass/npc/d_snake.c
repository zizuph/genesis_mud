/* 
 * /d/Kalad/common/wild/pass/npc/d_snake.c
 * Purpose    : A desert rattle snake, that poisons!
 * Located    : /d/Kalad/common/wild/pass/desert/rock
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("snake");
   set_race_name("snake");
   set_adj("large");
   add_adj("rattler");
   set_long("An extremely long and much larger version of the rattler "+
      "common to desert areas in Kalad. This creature is nearly ten feet "+
      "in length, and at its present coiled state is almost four feet in "+
      "height.\n");
   set_gender(G_NEUTER);
   set_stats(({40,65,40,5,5,40}));
   set_skill(SS_DEFENCE,30);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,3000);
   add_prop(CONT_I_VOLUME,3000);
   add_prop(OBJ_I_NO_INS, 1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   set_act_time(3);
   add_act("emote coils in warning.");
   add_act("emote hisses at you.");
   add_act("slithers around in circles.");
   add_act(({"kill human","kill elf","kill dwarf","kill gnome","kill hobbit","kill goblin"}));
   set_cact_time(3);
   add_cact("emote hisses angrily!");
   add_cact("emote bears its fangs.");
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 100, "immense fangs");
   set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 20, 20, 20 }), 80, "body");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy,"The large rattler snake's fangs burrow into your flesh!\n");
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(750);
         poison->set_interval(100);
         poison->set_strength(400);
         poison->set_damage(({POISON_HP, 300, POISON_STAT, SS_STR}));
         poison->start_poison();
      }
   }
   return 0;
}
