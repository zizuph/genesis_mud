/* the lost princess ariel */
inherit "/std/monster";
#include <macros.h>
#include "/sys/ss_types.h"
#include "defs.h"


create_monster()
{
   set_living_name("ariel");
   set_name(({"ariel","maiden"}));
   set_race_name("human");
   set_short("beautiful maiden");
   set_stats(({30,30,50,45,20,30}));
   set_long("This beatiful maiden seems to be imprisoned here against\n"+
      "her will.\n");
   set_adj("beautiful");
   
   set_alignment(750);
   
   set_gender(1);
   set_act_time(15);
   add_act(({"sigh","sulk","say Help me get out of here, please!","cry"}));
   
   set_cact_time(15);
   add_cact(({"scream","say You villain!","say Jerk!"}));
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   call_out("get_dress",1);
}

get_dress()
{
   object dress, stockings, dagger;
   
   dress   = clone_object(STAND_ARMOUR + "dress");
   stockings = clone_object(STAND_ARMOUR + "stockings");
   dagger = clone_object(STAND_WEAPON + "sd.c");
   
   if ( objectp(dress) )
      {
      dress->move(this_object());
   }
   if ( objectp(stockings) )
      {
      stockings->move(this_object());
   }
   if ( objectp(dagger) )
   {
	dagger->move(this_object());
   }
   command("wear all");
   command("wield all");
}
