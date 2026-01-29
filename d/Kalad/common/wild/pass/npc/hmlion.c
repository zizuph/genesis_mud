/* 
 * /d/Kalad/common/wild/pass/npc/hmlion.c
 * Purpose    : A lion
 * Located    : /d/Kalad/common/wild/pass/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
   set_name("lion");
   set_race_name("lion");
   set_adj("mountain");
   set_long("A magnificent beast, truly worthy of the title, king of "+
      "the mountains. For no other animal within the Hespyre mountains can "+
      "match its speed and bravery.\n");
   set_stats(({100,75,75,50,50,100}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,50);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT, 115000);
   add_prop(OBJ_I_VOLUME,25000);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(3);
   add_act("emote snarls slightly.");
   add_act("emote growls in warning.");
   set_cact_time(3);
   add_cact("emote roars loudly!");
   set_random_move(10);
   set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
   set_attack_unarmed(A_LCLAW, 45, 25, W_SLASH, 30, "left paw");
   set_attack_unarmed(A_RCLAW, 45, 25, W_SLASH, 30, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
   add_leftover("/d/Kalad/common/wild/pass/obj/lion_pelt","pelt",1,"",1,1);
}
