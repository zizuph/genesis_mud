/* 
 * /d/Kalad/common/wild/pass/npc/d_bat.c
 * Purpose    : A deep bat
 * Located    : /d/Kalad/common/wild/pass/underdark/
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
#define H_WINGS 2
#define H_LEGS 3
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("bat");
   set_race_name("bat");
   set_adj("desert");
   set_long("A plump rat-like animal with long leathery wings, its "+
      "blood red eyes and tiny fangs make it look far more vicious than its "+
      "small size would normally allow.\n");
   set_gender(G_NEUTER);
   set_stats(({20,30,20,15,15,20}));
   set_skill(SS_DEFENCE,30);
   set_act_time(6);
   add_act("emote makes a hight-pitched squeaking noise.");
   add_act("emote flaps its leathery wings.");
   set_cact_time(3);
   add_act("emote flaps its wings in a flurry!");
   add_act("emote turns its red eyes upon you.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_WEIGHT,5000);
   add_prop(CONT_I_VOLUME,5000);
   add_prop(OBJ_I_NO_INS,1);
   set_attack_unarmed(A_BITE, 20, 20, W_IMPALE, 40, "fanged teeth");
   set_attack_unarmed(A_LCLAW, 15, 15, W_SLASH, 30, "tiny left claw");
   set_attack_unarmed(A_RCLAW, 15, 15, W_SLASH, 30, "tiny right claw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 15 }), 40, "body");
   set_hitloc_unarmed(H_WINGS, ({ 10, 10, 10 }), 20, "leathery wings");
   set_hitloc_unarmed(H_LEGS, ({ 5, 5, 5 }), 20, "spindly legs");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote emits a high-pitched squeak.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
