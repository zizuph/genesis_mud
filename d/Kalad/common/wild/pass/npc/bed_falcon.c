/* 
 * /d/Kalad/common/wild/pass/npc/bed_falcon.c
 * Purpose    : The falcon in the bedellin camp
 * Located    : /d/Kalad/common/wild/pass/desert/camp
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
   set_name("falcon");
   set_race_name("falcon");
   set_adj("bedellin");
   add_adj("hunting");
   set_long("A beautiful predatory bird of prey, its graceful and "+
      "powerful form, coupled with its gift of flight leaves you feeling "+
      "mundane in comparison.\n");
   set_gender(G_NEUTER);
   set_stats(({50,75,50,25,25,60}));
   set_skill(SS_DEFENCE,50);
   set_act_time(6);
   add_act("emote screeches defiantly.");
   set_cact_time(3);
   add_cact("emote screeches in anger.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_WEIGHT,25000);
   add_prop(CONT_I_VOLUME,25000);
   add_prop(OBJ_I_NO_INS,1);
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 40, "beak");
   set_attack_unarmed(A_LCLAW, 35, 35, W_SLASH, 30, "left claw");
   set_attack_unarmed(A_RCLAW, 35, 35, W_SLASH, 30, "right claw");
   set_hitloc_unarmed(H_HEAD, ({ 15, 20, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 20 }), 40, "body");
   set_hitloc_unarmed(H_WINGS, ({ 10, 10, 10 }), 20, "wings");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote screeches angrily at you!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
