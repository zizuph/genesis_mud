#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("barkeeper");
    set_short("portly barkeeper");
    set_long("Before you stands a portly barkeeper. It " +
      "looks like from his many scars he used to be an " +
      "adventurer in his youth, but now occupies his time serving " +
      "drinks in Hawkstones Taproom.\n");
    set_stats(({60,60,60,60,60,60}));
    set_hp(10000);


    add_ask("quest","say Sorry, I dont know of any quests. " +
      "But I have heard that there is a Knight of Solamnia " +
      "in town incognito, searching for a family heirloom " +
      "that was seen in Flotsam.",1);
    set_act_time(5);
    add_act("emote wipes down the bar with a dirty rag.");
    add_act("emote warms his hands at the fireplace.");
    add_act("emote eyes you suspiciously.");

}
