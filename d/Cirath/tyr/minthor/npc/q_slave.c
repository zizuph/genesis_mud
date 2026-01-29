inherit "/std/monster.c";
#include "defs.h"
#include <wa_types.h>
#include "/d/Cirath/quest_handler/quest_handler.h"
#include "/sys/filter_funs.h"
create_monster()
{
   set_name("slave");
   set_race_name("human");
   set_adj("weak"); 
   add_adj("whimpering");
   set_long("This is one of the most pitiful slaves you have ever seen. "
	+"He has no muscle definition, and its a wonder he can walk "
	+"without assistance.\n");
   set_stats(({10,20,15,5,5,10}));
   set_act_time(3);
   add_act("groan");
   add_act("emote wipes the sweat from his brow.");
   add_act("emote winces in pain.");
   add_act("emote begs for help.");
   set_cact_time(3);
   add_cact("gasp");
   add_cact("emote cowers in the corner.");
   set_chat_time(3);
   add_chat("Please help me.\n");
   add_chat("Don't whip me anymore.\n");
   add_chat("These crates are really heavy.\n");
   set_cchat_time(3);
   add_cchat("Why?\n");
   add_cchat("Please stop!\n");
   add_cchat("I never hurt you.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
}


help(string s)
{
   	notify_fail("No help available on that topic.\n");
   	if(s!="slave")
      		return 0;   		
       	
        
        if (!QH_QUERY_QUEST_COMPLETED(TP, "slave1"))
      	{
      		TP->catch_msg("You help the slave by lifting a heavy crate.\n");
      		say(QCTNAME(TP)+" helps the slave lift a crate.\n");
      		QH_QUEST_COMPLETED(TP,"slave1");
      		TP->catch_msg("You feel more experienced!\n");
      		return 1;
   	}
   	else
   	return 0;
}


init_living()
{
::init_living();
add_action("help","help");
}
