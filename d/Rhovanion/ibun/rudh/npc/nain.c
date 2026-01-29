   inherit "/std/monster";

#include "/d/Rhovanion/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>

   void
   create_monster()
   {
      set_name("nain");
      set_race_name("dwarf");
      set_adj("strong");
      set_long("Dwarves are strong, and this one is one of the stronger ones.\n");

               /* STR DEX CON INT WIS DIS */
      set_stats(({ 15, 13, 19,  3,  3, 70 })); /* Set his stats */
      set_hp(1000);           /* Heal him fully */
      
      set_chat_time(10);      /* Set the time between speaking    */
      add_chat("Go away!");   /* Add some lines to say (randomly) */
      add_chat("Who are you?");
      add_chat("Go hither, foul creature!");

      set_cchat_time(4);      /* Set some combat chat lines */
      add_cchat("This is that one, fatal mistake!");
      add_cchat("Prepare to die!");

      set_act_time(7);        /* Set some random actions */
      add_act("growl");
      add_act("grin");
  }
