inherit "/std/monster";

#include <ss_types.h>
#include "default.h"

void
create_monster()
{
   if (!IS_CLONE)
      return;
   
    set_name("man");
    set_adj("militia");
    set_short("militia man");
   set_race_name("elf");
   set_pshort("militia");
   set_long("This young Elven adult has just entered the "+
      "army and must serve in the militia to gain combat skills. He "+
      "looks pretty inexperienced.\n");
   
   set_base_stat(SS_INT, 23);
   set_base_stat(SS_WIS, 22);
   set_base_stat(SS_DIS, 20);
   set_base_stat(SS_STR, 21);
   set_base_stat(SS_DEX, 23);
   set_base_stat(SS_CON, 19);
   
   set_skill(SS_WEP_SWORD, 24);
   set_skill(SS_2H_COMBAT, 17);
   set_skill(SS_PARRY, 24);
   
   set_all_hitloc_unarmed(3);
   
   set_hp(569);
   
   add_prop(OBJ_I_WEIGHT, 19000);
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_alignment(250);
   
   
   call_out("arm_me", 1);
}

void
arm_me()
{
   object eq;
   
   eq=clone_object(CASTLE_DIR + "wep/m_sword");
   if (eq)
      eq->move(this_object());
   eq = clone_object(CASTLE_DIR + "wep/m_knife");
   if(eq)
      eq->move(TO);
   eq=clone_object(CASTLE_DIR + "arm/m_leather");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/m_cloak");
   if (eq)
      eq->move(this_object());
   command("wield all");
    command("wear leather armour");
   command("wear all");
}
