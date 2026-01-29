/*
 *  Frog for the rivershore
 */

#pragma save_binary

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_monster()
{
   int rand;

   if (!IS_CLONE)
      return;
   set_name("frog");
   set_race_name("frog"); 
   set_adj("small");
   set_long("The frog jumps in and out of the reeds.\n");

   default_config_npc();
   rand = random(5);
   set_base_stat(SS_CON, 4 + rand);
   set_hp(40 + rand*10);

   set_chat_time(5);
   add_chat("Hriibit!");
   add_chat("Hriiiiibit, Hriiibit!");

   add_prop(CONT_I_WEIGHT, 400);   /* 0.400 Kg  */
   add_prop(CONT_I_VOLUME, 400);   /* 0.400 Ltr */
}
