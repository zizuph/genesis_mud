inherit "/std/monster";

#include "default.h"

void
create_monster()
{
   set_name("maid");
   set_race_name("elf");
   set_short("maid");
   set_long("This young elf is the Mistress's maid, who is cleaning the " +
            "rooms whilst the family are away. She looks rather innocent " +
            "and young.\n");
   
   set_base_stat(SS_STR, 21);
   set_base_stat(SS_DEX, 20);
   set_base_stat(SS_CON, 25);
   set_base_stat(SS_INT, 13);
   set_base_stat(SS_WIS, 10);
   set_base_stat(SS_DIS, 20);
   
   set_skill(SS_DEFENCE, 16);
   set_skill(SS_PARRY, 15);
   
   set_hp(325);
   set_gender(1);
   
   add_prop(CONT_I_WEIGHT, 35000);
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(CONT_I_VOLUME, 35500);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("Can I help you?");
   add_chat("These rooms are private, you're not supposed to be here.");
   add_chat("What are you doing in here?");

   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("Please don't kill me!");
   add_cchat("No, no....");
   add_cchat("HELP!");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("curtsey");
   add_act("ponder");
   add_act("eyebrow");
}

