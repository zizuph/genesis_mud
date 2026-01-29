inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("golem");
   add_name("warrior");
   set_race_name("golem");
   set_adj("stone");
   set_gender(G_NEUTER);
   set_short("stone golem");
   set_long("A perfect example of a drow warrior, save for the fact that "+
      "this warrior is constructed not of flesh, but of stone. The "+
      "black stone has been so exquisitely-crafted that you would be "+
      "hard-pressed to distinguish this figure from any other drow warrior, "+
      "save for the fact that this warrior is well over nine feet in height.\n");
   for (i = 0; i < 3; i++)
   set_base_stat(i, 125 + random(50));
   set_base_stat(3, 100);
   set_base_stat(4, 100);
   set_base_stat(5, 150);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,60);
   set_knight_prestige(1000);
   set_attack_unarmed(0, 50, 50, W_BLUDGEON, 30, "right stone fist");
   set_attack_unarmed(1, 50, 50, W_BLUDGEON, 30, "left stone fist");
   set_attack_unarmed(2, 45, 45, W_BLUDGEON, 20, "right stone foot");
   set_attack_unarmed(3, 45, 45, W_BLUDGEON, 20, "left stone foot");
   set_hitloc_unarmed(1, 75, 15, "stone head");
   set_hitloc_unarmed(2, 70, 10, "right stone arm");
   set_hitloc_unarmed(3, 70, 10, "left stone arm");
   set_hitloc_unarmed(4, 95, 45, "stone body");
   set_hitloc_unarmed(5, 90, 20, "stone legs");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_WEIGHT,900000);
   add_prop(CONT_I_VOLUME,900000);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_act_time(3);
   add_act("get all");
   add_act("get all from corpse");
   add_act("emote moves around, creating a grating noise with its body.");
   set_aggressive(1);
   set_attack_chance(75);
}
do_die(object killer)
{
   object corpse;
   if (query_hp() > 0) return;
   
   corpse = clone_object(CPASS(uc/obj/d_stone_golem));
   corpse->move(environment(TO));
   
   ::do_die(killer);
}
