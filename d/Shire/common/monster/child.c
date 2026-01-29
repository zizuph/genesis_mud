inherit "/std/monster";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"

int tied_up;

create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name(({"child","girl","human"}));
   set_adj("sad");
   set_race_name("human"); 

   add_prop(CONT_I_WEIGHT,50000);  /* 102 Kg */
   add_prop(CONT_I_HEIGHT,63);     /* 63 cm */

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 13, 22, 27, 15, 10, 5}));
   set_hp(10000); /* Heal fully */
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,30);

   /* Actions */
   set_act_time(5);
   add_act("cry");
   add_act("sniff");

   set_chat_time(5);
   add_chat("Where is Luis?");
   add_chat("Have you seen my mother??");
   add_chat("The boogy man has my brother.");

   /* Combat chat-strings */
   set_cchat_time(5);
   add_cchat("Don't beat me, please!");
   add_cchat("Haven't I suffered enough?");
   add_cchat("I'll call my daddy!");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet her */
}
