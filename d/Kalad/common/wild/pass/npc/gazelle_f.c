/* 
 * /d/Kalad/common/wild/pass/npc/gazelle_f.c
 * Purpose    : A deer like creature
 * Located    : /d/Kalad/common/wild/pass/desert/oasis/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LHOOF 1
#define A_RHOOF 2
#define A_HORNS 3
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("gazelle");
   set_race_name("gazelle");
   set_adj("nimble");
   set_long("A creature vaguely resembling a small deer. Its brownish-white "+
      "fur suits it well, for it matches the color of the surrounding "+
      "grassland. A pair of dainty horns sprout from its head.\n");
   set_stats(({40,70,40,30,30,40}));
   set_skill(SS_DEFENCE,30);
   set_gender(G_FEMALE);
   set_random_move(10);
   set_act_time(9);
   add_act("emote munches on some grass.");
   add_act("emote makes a soft blurting sound.");
   add_act("emote moves its head around, looking for possible danger.");
   set_cact_time(6);
   add_cact("emote makes a noisome sound.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_WEIGHT,35000);
   add_prop(CONT_I_VOLUME,35000);
   add_prop(OBJ_I_NO_INS,1);
   set_attack_unarmed(A_BITE, 20, 20, W_BLUDGEON, 20, "teeth");
   set_attack_unarmed(A_LHOOF, 30, 20, W_BLUDGEON, 30, "left hoof");
   set_attack_unarmed(A_RHOOF, 30, 20, W_BLUDGEON, 30, "right hoof");
   set_attack_unarmed(A_HORNS, 20, 35, W_BLUDGEON, 20, "dainty horns");
   set_hitloc_unarmed(H_HEAD, ({ 20, 15, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 20 }), 60, "body");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 15 }), 20, "legs");
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote snorts angrily!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
