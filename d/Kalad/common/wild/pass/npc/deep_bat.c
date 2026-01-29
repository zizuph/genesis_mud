/* 
 * /d/Kalad/common/wild/pass/npc/deep_bat.c
 * Purpose    : A deep cave bat
 * Located    : /d/Kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL 3
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
   set_name("bat");
   set_race_name("bat");
   set_adj("deep");
   set_long("An extremely large bat, its wingspan must be at least seven "+
      "feet. Colored in velvet black fur, the creature blends in almost "+
      "perfectly with the dark stone around it, the bat's red eyes stare at you "+
      "maliciously.\n");
   set_stats(({25,20,20,15,15,25}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,30);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,30000);
   add_prop(OBJ_I_VOLUME,25000);
   add_prop(OBJ_I_NO_INS,1);
   add_prop(LIVE_I_SEE_DARK,10);
   set_act_time(6);
   add_act("emote emits a high-pitched screech.");
   add_act("emote shifts around on its perch on the ceiling.");
   set_cact_time(3);
   add_cact("emote screeches angrily!");
   set_random_move(10);
   set_alignment(-30);
   set_knight_prestige(30);
   set_attack_unarmed(A_BITE, 15, 20, W_IMPALE, 35, "bite");
   set_attack_unarmed(A_LCLAW, 25, 15, W_SLASH, 25, "left wing claw");
   set_attack_unarmed(A_RCLAW, 25, 15, W_SLASH, 25, "right wing claw");
   set_attack_unarmed(A_TAIL, 20, 25, W_IMPALE, 15, "razor-sharp tail");
   set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 25 }), 80, "body");
}
