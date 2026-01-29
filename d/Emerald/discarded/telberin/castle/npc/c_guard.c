inherit "/std/monster";

#include "default.h"
#define HOME_DIR        "/d/Emerald/"


void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("guard");
   set_race_name("elf");
   set_short("court guard");
   set_adj("court");
   set_long("This huge looking guard is one who is highly "+
      "trained and will give his life for his Kingdom. He does not "+
      "look like someone who you will mess with.\n");
   
   set_base_stat(SS_INT, 77);
   set_base_stat(SS_WIS, 68);
   set_base_stat(SS_DIS, 67);
   set_base_stat(SS_STR, 78);
   set_base_stat(SS_DEX, 80);
   set_base_stat(SS_CON, 75);
   
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_PARRY, 70);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_UNARM_COMBAT, 80);
   
   set_all_hitloc_unarmed(6);
   
   set_hp(950);
   
   add_prop(OBJ_I_WEIGHT, 100000);
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_alignment(790);
   
   
}

void
arm_me()
{
   object eq;
   
   eq=clone_object(HOME_DIR + "wep/patrol_longsword");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/sil_gre");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/sil_hel");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/sil_bra");
   if(eq)
      eq->move(this_object());
   command("wield all");
   command("wear all");
}
