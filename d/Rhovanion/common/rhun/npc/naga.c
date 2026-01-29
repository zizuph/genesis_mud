
inherit "/d/Rhovanion/lib/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_monster()
{
	set_race_name("human");
	set_name("woman");
	set_adj("old");
	add_adj("gossipy");
	add_name("Naga");
	add_name("_gossip_woman_");

        set_alignment(50);
	set_gender(1);
	set_short("old gossipy woman");
	set_long("This old woman appears to hang out at the town hall, looking for"
	       + " gossip and giving it out whether you like it or not.\n");
	add_prop(CONT_I_WEIGHT, 70 * 1000);
	add_prop(CONT_I_VOLUME, 70 * 1000);
	add_prop(CONT_I_HEIGHT, 168);
	set_stats(({
		20, 25, 20, 25, 25, 20
	}));
	set_hp(query_max_hp());

	set_skill(SS_UNARM_COMBAT, 12);
	set_skill(SS_DEFENCE, 12);
	set_pick_up(43);

	set_chat_time(3);
	add_chat("The guards will protect us; I'm sure of it.");
	add_chat("My neighbour's nephew was blown off the ship when he didn't go below.");
	add_chat("The hag lives all alone in the ruins. She's raving mad you know, but I can't help but to feel sorry for her.");
	add_chat("The trolls in the hills are true widow-makers, I tell you!");
	add_chat("My son and his friends went away to explore the citadel south of the Sea, but they never returned.");
	add_chat("The Easterlings have a hideout in the forest. Everyone knows it, but the mayor says there is no proof, so he can't"
		 + " request any help.");

	set_cchat_time(5);
	add_cchat("Killing an old woman!? Your should be ashamed of yourself!.");
	add_cchat("HELP! GUARDS!");

	set_act_time(4);
	add_act("stretch");
	add_act("spit");
	add_act("cackle");
	add_act("grin");
	add_act("groan");
	add_act("sniff");
}
