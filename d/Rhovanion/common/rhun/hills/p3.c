
inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

init()
{
        ::init();
	add_action("climb_crack", "climb");
}

create_room()
{
	set_short("Mountain path");
	set_long("You follow this very-narrow path as it curves " +
		 "along the mountains, here leading from southwest to east.  High " +
		 "above you, brewing clouds signal the approach of " +
		 "a storm.\n");

	add_exit(RHUN_DIR + "hills/p2", "east");
	add_exit(RHUN_DIR + "hills/p4", "southwest");

	add_item("path", "The path heads off to the east and " +
		 "southwest from here, winding its way along the cliff's " +
		 "edge.\n");
	add_item(({
		"mountain", "peak", "up"
	}), "The moutain peak " +
		"along whose edge you follow is quite tall and forbidding, " +
		"rising up far above your head. You think you can see a ledge"
		+ " high above.\n");
	add_item("ledge", "It's very far up.\n");
	add_prop(OBJ_S_SEARCH_FUN, "searchfunp3");
	add_prop(OBJ_I_SEARCH_TIME, 20);
	add_item("crack", "It looks hard to climb.\n");
	add_item(({
		"sky", "overhead", "clouds", "storm"
	}), "Dark clouds " +
		"hang overhead, predicting the onslaught of a storm.\n");
}

string
searchfunp3(object searcher, string str)
{
	if ((str == "ledge")  && (searcher->query_skill(SS_AWARENESS) > 15))
		return "You search patiently for a way up to the ledge and find a crack leading up to it!\n";
	else
		return "Your search reveals nothing special.\n";
}

int
climb_crack(string str)
{
	NF("Climb what?");
	if (str != "crack")
		return 0;

	/* ok, lets try to climb the crack. */
	if (TP->query_skill(SS_CLIMB) > (20 + random(6))) {
		/* success */
		TP->catch_msg("You slowly climb up the crack.");
		tell_room(environment(), QCTNAME(TP) + " slowly climbs up the mountain.\n", TP);
		TP->move_living("M", RHUN_DIR + "hills/ledge", 1);
	} else {
		TP->catch_msg("You try to climb up the crack but slip and scrape your hands.\n");
		TP->heal_hp(-10);	/* shouldn't die from this, so i
					 * don't call do_die */
		tell_room(environment(), QCTNAME(TP) + " tries to climb up the mountain but slips and falls down again.\n");
	}
	return 1;
}

