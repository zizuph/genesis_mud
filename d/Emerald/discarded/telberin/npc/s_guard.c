inherit "/std/monster";

#include "default.h"

/* This is a beefed up guard I would like to add to telberin */

void
create_monster()
{
   set_name("guard");
   set_race_name("elf");
   set_short("guard");
   set_long("By his tabard you guess that this must be a "+
      "guard seargent for the city of Telberin.  He has seen "+
      "battle in his time and seems confident of himself. \n");
   
   set_base_stat(SS_INT, 48);
   set_base_stat(SS_WIS, 48);
   set_base_stat(SS_DIS, 50);
   set_base_stat(SS_STR, 55);
   set_base_stat(SS_DEX, 58);
   set_base_stat(SS_CON, 45);
   
   set_skill(SS_WEP_SWORD, 52);
   set_skill(SS_2H_COMBAT, 52);
   set_skill(SS_PARRY, 45);
   set_skill(SS_DEFENCE, 58);
   
   set_all_hitloc_unarmed(3);
   
   add_chat("I hope you enjoy our town.") ;
   add_chat("I hear the King will send us reinforcements soon!") ;
   add_prop(CONT_I_WEIGHT, 33000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);
   add_prop(CONT_I_VOLUME, 40000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_alignment(250);
}


void
arm_me()
{
   clone_object(WEP_DIR + "g_sword")->move(this_object(), 1);
   clone_object(WEP_DIR + "dagger")->move(this_object(), 1);
   clone_object(ARM_DIR + "g_brig")->move(this_object(), 1);
   clone_object(ARM_DIR + "g_helmet")->move(this_object(), 1);
   command("wield all");
   command("wear all");
}
