/* 
 * /d/Kalad/common/wild/pass/npc/d_lion.c
 * Purpose    : A desert lion
 * Located    : /d/Kalad/common/wild/pass/desert/rock
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("lion");
   set_race_name("lion");
   set_adj("powerful");
   add_adj("desert");
   set_long("A fierce and powerful predator of the waste, its unmatched "+
      "strength and gracefulness prove beyond a doubt that it is the king "+
      "of the beasts.\n");
   set_gender(G_NEUTER);
   set_stats(({100,100,100,50,50,100}));
   set_skill(SS_DEFENCE,40);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_random_move(10);
   set_act_time(3);
   add_act("snarl all");
   add_act("growl all");
   add_act("emote roars loudly!");
   set_cact_time(3);
   add_cact("emote bellows out a fearsome roar!!");
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 10, "crushing jaws");
   set_attack_unarmed(A_LPAW, 25, 25, W_SLASH, 45, "left paw");
   set_attack_unarmed(A_RPAW, 25, 25, W_SLASH, 45, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 25, 30 }), 20, "maned head");
   set_hitloc_unarmed(H_BODY, ({ 25, 30, 35 }), 60, "large body");
   set_hitloc_unarmed(H_LEGS, ({ 15, 20, 25 }), 20, "strong legs");
   add_leftover("/d/Kalad/common/wild/pass/obj/lion_pelt","pelt",1,"",1,1);
}
