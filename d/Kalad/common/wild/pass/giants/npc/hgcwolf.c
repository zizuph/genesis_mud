/* 
* /d/Kalad/common/wild/pass/giantpass/npc/hgcwolf.c
* Purpose    : A dire wolf
* Located    : /d/Kalad/common/wild/pass/giantpass/rooms/nhut
* Created By : Antharanos ??.??.??
* Modified By: Meton 2020
*/ 

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/d/Kalad/std/group_cluster.c";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/std/act/attack.c"
#include "/d/Kalad/defs.h"
#include "../local.h"


#define A_BITE  1
#define A_LCLAW 2
#define A_RCLAW 4

#define H_HEAD 1
#define H_BODY 2
/* by Antharanos */
void
create_creature()
{
   set_name("wolf");
   add_name("_hgiant_friends");
   set_race_name("wolf");
   set_adj("enormous");
   add_adj("dire");
   set_pshort("huge dire wolves");
   set_long(one_of_list(WOLFDESC));
   set_stats(({120,115,110,120,120,120}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,50);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,30000);
   add_prop(OBJ_I_NO_INS,1);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_prospective_cluster(({"_hgiant_friends"}));
   set_act_time(6);
   add_act("snarl all");
   add_act("growl all");
   set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
   set_attack_unarmed(A_LCLAW, 20, 15, W_SLASH, 30, "left paw");
   set_attack_unarmed(A_RCLAW, 20, 15, W_SLASH, 30, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
   add_leftover(one_of_list(WOLFITEM), "weird bulge in the stomach", 1, 0, 1, 0, 10);

   set_exp_factor(130);

}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      command("emote snarls angrily!");
   command("emote prepares to rip your throat out!");
   command("kill " + lower_case(ob->query_real_name()));
}
