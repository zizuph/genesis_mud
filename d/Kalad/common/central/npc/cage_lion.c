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
   set_name("lion");
   set_race_name("lion");
   set_adj("mountain");
   set_long("A vicious-looking beast from the Hespyre mountains. It "+
      "looks as if it hasn't eaten in awhile.\n");
   set_stats(({100,75,75,50,50,100}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,50);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT, 115000);
   add_prop(OBJ_I_VOLUME, 20000);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(3);
   add_act("snarl all");
   add_act("growl all");
   set_aggressive(1);
   set_random_move(10);
   set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
   set_attack_unarmed(A_LCLAW, 45, 25, W_SLASH, 30, "left paw");
   set_attack_unarmed(A_RCLAW, 45, 25, W_SLASH, 30, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
}
