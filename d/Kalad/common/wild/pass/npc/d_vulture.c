/* 
 * /d/Kalad/common/wild/pass/npc/d_vulture.c
 * Purpose    : A desert vulture, of course.
 * Located    : /d/Kalad/common/wild/pass/desert/
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
   set_name("vulture");
   set_race_name("vulture");
   set_adj("eerie");
   add_adj("black");
   set_long("A scrawny-looking vulture possessing ink-black feathers and a "+
      "tremendous wing span. Its dull red head sits upon a twisted and "+
      "skinny neck, allowing it to swivel its head around in wide arcs. "+
      "There's something about its eerie black eyes that unnerves you, "+
      "buy you cannot discern why.\n");
   set_gender(G_NEUTER);
   set_stats(({40,60,40,20,20,40}));
   set_skill(SS_DEFENCE,30);
   set_act_time(6);
   add_act("emote emits an odd croaking sound.");
   set_cact_time(3);
   add_cact("emote a horrendous croaking sound.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_WEIGHT,25000);
   add_prop(CONT_I_VOLUME,25000);
   add_prop(OBJ_I_NO_INS,1);
   set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 40, "beak");
   set_attack_unarmed(A_LCLAW, 25, 25, W_SLASH, 30, "left claw");
   set_attack_unarmed(A_RCLAW, 25, 25, W_SLASH, 30, "right claw");
   set_hitloc_unarmed(H_HEAD, ({ 15, 20, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 15 }), 40, "body");
   set_hitloc_unarmed(H_WINGS, ({ 10, 10, 10 }), 20, "wings");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote croaks loudly!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
