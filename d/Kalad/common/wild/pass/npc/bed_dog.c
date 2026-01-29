/* 
 * /d/Kalad/common/wild/pass/npc/bed_dog.c
 * Purpose    : A bedellin dog
 * Located    : /d/Kalad/common/wild/pass/desert/camp
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
   set_name("dog");
   set_race_name("dog");
   set_adj("bedellin");
   add_adj("hunting");
   set_long("A long-bodied, sleek animal trained by the Bedellin nomads "+
      "to aid in matters of hunting as well as warfare. It is truly a "+
      "prized possession.\n");
   set_gender(G_NEUTER);
   set_stats(({40,70,40,25,25,60}));
   set_skill(SS_DEFENCE,30);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,40000);
   add_prop(CONT_I_VOLUME,40000);
   add_prop(OBJ_I_NO_INS, 1);
   set_random_move(10);
   set_act_time(3);
   add_act("growl .");
   add_act("emote barks softly.");
   add_act("emote starts sniffing you.");
   set_cact_time(3);
   add_cact("growl all");
   add_cact("snarl all");
   add_cact("emote barks loudly!");
   set_attack_unarmed(A_BITE, 25, 25, W_IMPALE, 10, "jaws");
   set_attack_unarmed(A_LPAW,   25, 15, W_SLASH, 45, "left paw");
   set_attack_unarmed(A_RPAW,   25, 15, W_SLASH, 45, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 20 }), 60, "body");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
}
