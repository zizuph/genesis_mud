/* 
 * /d/Kalad/common/wild/pass/npc/d_hare.c
 * Purpose    : A desert bunny
 * Located    : /d/Kalad/common/wild/pass/desert/
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
   set_name("hare");
   set_race_name("hare");
   set_adj("small");
   add_adj("desert");
   set_long("A small, innocent-looking creature with short golden-brown "+
      "fur. It has long tapered ears, a twitching nose and a small fluffy "+
      "tail. In all entirety, it is a very unthreatening animal in a very "+
      "threatening land.\n");
   set_gender(G_NEUTER);
   set_stats(({15,15,15,10,10,10}));
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,10000);
   add_prop(CONT_I_VOLUME,10000);
   add_prop(OBJ_I_NO_INS, 1);
   set_random_move(10);
   set_act_time(3);
   add_act("emote nibbles on some grass.");
   add_act("emote twitches its nose.");
   set_cact_time(3);
   add_cact("emote looks very frightened.");
   set_attack_unarmed(A_BITE, 10, 10, W_BLUDGEON, 10, "teeth");
   set_attack_unarmed(A_LPAW, 5, 5, W_BLUDGEON, 45, "left paw");
   set_attack_unarmed(A_RPAW, 5, 5, W_BLUDGEON, 45, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 5, 10, 10 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 10, 15 }), 60, "body");
   set_hitloc_unarmed(H_LEGS, ({ 5, 5, 5 }), 20, "legs");
}
