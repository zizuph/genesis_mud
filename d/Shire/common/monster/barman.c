  /*  bartender of pub in sparkle  */
inherit "/std/monster";
#include <macros.h>

#include "/sys/ss_types.h"
create_monster()
{
   set_name("bartender");
  set_race_name("human");
    set_short("bartender");
    set_stats(({100,50,50,1,1,20}));
   set_long(break_string("The bartender is here to serve you. Just order "
	+  "what you want.\n",50));


   set_act_time(1);
   add_act(({"say Please, buy a drink and relax.","say Welcome!"}));


   set_cact_time(1);
   add_cact(({"say So, my beer's not good enough for you?","puke all",
	      "say I'll see you in hell"}));
  set_skill(SS_DEFENCE,50);
  set_skill(SS_PARRY,50);
}
