/* 
 * /d/Kalad/common/wild/pass/npc/g_lizard.c
 * Purpose    : A giant lizard
 * Located    : /d/Kalad/common/wild/pass/desert/rock
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_HORNS 3
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("lizard");
   set_race_name("lizard");
   set_adj("giant");
   add_adj("horned");
   set_long("A monstrously larger version of the typical desert lizard, this "+
      "creature is a full fifteen feet in length from its scaled snout "+
      "to the tip of its tail. Angry red eyes are lodged in its large "+
      "skull, while a long forked tongue flickers from its gaping mouth. "+
      "The creature's sandy brown scales seem perfectly suited for allowing "+
      "it to blend into the harsh environment of the waste.\n");
   set_gender(G_NEUTER);
   set_stats(({75,50,75,25,25,75}));
   set_skill(SS_DEFENCE,30);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,200000);
   add_prop(CONT_I_VOLUME,200000);
   add_prop(OBJ_I_NO_INS, 1);
   set_random_move(10);
   set_act_time(3);
   add_act("emote flickers its tongue.");
   add_act("emote swivels its horned head from side to side.");
   add_act(({"kill human","kill elf","kill dwarf","kill gnome","kill hobbit","kill goblin"}));
   set_cact_time(3);
   add_cact("emote flickers its tongue out at you.");
   add_cact("emote swipes its long tail at you.");
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 15, "razor-sharp teeth");
   set_attack_unarmed(A_LCLAW, 25, 25, W_SLASH, 35, "left claw");
   set_attack_unarmed(A_RCLAW, 25, 25, W_SLASH, 35, "right claw");
   set_attack_unarmed(A_HORNS, 35, 35, W_IMPALE, 15, "sharp horns");
   set_hitloc_unarmed(H_HEAD, ({ 30, 35, 40 }), 20, "horned head");
   set_hitloc_unarmed(H_BODY, ({ 35, 40, 40 }), 60, "large body");
   set_hitloc_unarmed(H_LEGS, ({ 25, 30, 35 }), 20, "thick legs");
}
