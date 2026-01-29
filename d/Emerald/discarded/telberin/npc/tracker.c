inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include "default.h"

void
create_monster()
{
   set_name("tracker");
   set_race_name("elf");
   set_short("elven tracker");
   set_long("This elven tracker is closely examining the ground for " +
            "something.\n");
   
   set_base_stat(SS_STR, 20);         
   set_base_stat(SS_DEX, 19);         
   set_base_stat(SS_CON, 25);         
   set_base_stat(SS_INT, 20);
   set_base_stat(SS_WIS, 20);
   set_base_stat(SS_DIS, 30);
   
   set_skill(SS_WEP_SWORD, 30);
   set_skill(SS_DEFENCE, 20);
   set_skill(SS_PARRY, 30);
   set_alignment(300);
   
   add_prop(OBJ_I_WEIGHT, 5000);
   
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("Have you seen the criminal?");
   add_chat("I can't see his tracks anywhere.");
   
   
   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("Hey! Leave me alone!");
   add_cchat("Help! Someone help me!");
   
   
   set_act_time(15);                    /* Set action interval           */
   add_act("ponder");
   add_act("think");
}

void
arm_me()
{
    object eq;

    clone_object(WEP_DIR + "foil")->move(this_object(), 1);
    clone_object(ARM_DIR + "l_bre")->move(this_object(), 1);
    clone_object(ARM_DIR + "l_hel")->move(this_object(), 1);
    clone_object(ARM_DIR + "l_cui")->move(this_object(), 1);
    command("wield all");
    command("wear all");
}
