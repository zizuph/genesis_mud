/* 
 * /d/Kalad/common/wild/pass/npc/dwolf.c
 * Purpose    : Dire wolf, larger wolf
 * Located    : /d/Kalad/common/wild/pass
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
   set_name("wolf");
   set_race_name("wolf");
   set_adj("huge");
   add_adj("dire");
   set_pshort("huge dire wolves");
   set_long("An enormous shaggy wolf. The large size indicates this wolf "+
      "belongs to the dire family of wolves, a larger and more aggressive "+
      "variety of the common wolf.\n");
   set_stats(({80,75,70,40,40,80}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,50);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,30000);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(6);
   add_act("snarl all");
   add_act("growl all");
   set_aggressive(1);
   set_random_move(10);
   set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
   set_attack_unarmed(A_LCLAW, 20, 15, W_SLASH, 30, "left paw");
   set_attack_unarmed(A_RCLAW, 20, 15, W_SLASH, 30, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      command("emote snarls angrily!");
   command("emote prepares to rip your throat out!");
   command("kill " + lower_case(ob->query_real_name()));
}
