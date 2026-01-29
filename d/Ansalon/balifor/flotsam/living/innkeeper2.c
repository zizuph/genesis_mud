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

    set_name("innkeeper");
    set_short("nervous innkeeper");
    set_long("This is the Innkeeper of the Saltbreeze Inn. He " +
      "seems tense and nervous, as if awaiting something. \n");
    set_stats(({16,16,50,16,16,16}));
    set_hp(10000);
    set_alignment(0);
    set_knight_prestige(-2);

    set_skill(SS_DEFENCE, 20);

    set_act_time(10);
    add_act("say I am afraid all the rooms are booked " +
      "out.");
    add_act("emote yawns as he goes over his account books.");
    add_act("say I doubt the Highlord will return tonight " +
      "in this weather.");
    add_act("peer nervous gakhan");

    add_ask("room","say Sorry, no rooms available.",1);
    add_ask("quest","say Sorry, dont know of any.",1);
    add_ask(({"kitiara","highlord"}),"say Sorry, the " +
      "Highlord left for Solamnia. I do not know when " +
      "she will return.",1);
}
