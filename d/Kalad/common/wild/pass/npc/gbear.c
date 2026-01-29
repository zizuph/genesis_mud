/* 
 * /d/Kalad/common/wild/pass/npc/gbear.c
 * Purpose    : A bear in the pass
 * Located    : /d/Kalad/common/wild/pass/
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
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
   set_name("bear");
   set_race_name("bear");
   set_adj("large");
   add_adj("grizzly");
   set_long("One of the dangerous grizzly bears that dwell within the "+
      "ranges of the Hespyre mountains. They are known for their nasty "+
      "tempers. Better leave now before it gets irritated.\n");
   set_stats(({100,75,100,40,40,100}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,50);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,150000);
   add_prop(OBJ_I_VOLUME,50000);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(3);
   add_act("emote growls slightly.");
   add_act("emote growls in warning.");
   set_cact_time(3);
   add_cact("emote roars loudly in anger!");
   set_random_move(10);
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 40, "jaws");
   set_attack_unarmed(A_LCLAW, 45, 25, W_SLASH, 30, "left paw");
   set_attack_unarmed(A_RCLAW, 45, 25, W_SLASH, 30, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
}
