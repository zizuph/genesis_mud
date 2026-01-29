inherit "/std/monster";
#include "defs.h"
#include  "/sys/money.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#include "/sys/filter_funs.h"
create_monster()
{
   set_name("slave");
   set_race_name("half-elf");
   set_adj("thirsty");
   set_short("thirsty slave half-elf");
   set_long("This slave keeps watch over the gardens. He looks very "
	+"thirsty.\n");
   set_stats(({10,10,10,15,15,10}));
   set_act_time(3);
   add_act("sigh");
   add_act("emote looks longingly at the pool of water.");
   add_act("ponder");
   add_act("emote prunes a bush.");
   set_cact_time(3);
   add_cact("emote cries in pain and disbelief.");
   add_cact("cry");
   set_chat_time(3);
   add_chat("I am so thirsty.\n");
   add_chat("The master cast a spell on me, i can't drink the water from the pool.\n");
   add_chat("I do not like being a slave.\n");
   add_chat("Can't you please aid me?");
   set_cchat_time(3);
   add_cchat("What have I done to you?\n");
   add_cchat("I only wanted some water.\n");
   add_cchat("Guards? Can you help me?\n");
}
aid(string s)
{
   	notify_fail("What?\n");
    	if(s!="slave")
      	return 0;  	   		
   	
   	if (!QH_QUERY_QUEST_COMPLETED(TP, "slave2"))
      	{
      		TP->catch_msg("You take a cup from the shrine and give the slave some water.\n");
   		say(QCTNAME(TP)+" gives the slave a drink of water.\n");
      		QH_QUEST_COMPLETED(TP,"slave2");
      		TP->catch_msg("You feel more experienced!\n");
      		return 1;
   	}
   	else
   	return 1;
}

init_living()
{
::init_living();
add_action("aid","aid");
}
