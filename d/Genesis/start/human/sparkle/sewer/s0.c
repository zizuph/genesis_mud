inherit "/w/erane/sewer/sewer";

#include <stdproperties.h>
#include <macros.h>
#include "sewer.h"

public void
create_room()
{
	::create_room();

    set_short("Sewer chamber");
	set_long("You are in a dank cavernous chamber within the " +
		"sewers of Sparkle. The walls around you glisten and " +
		"drip with moisture; the sludgy ground beneath you, " +
		"an ankle-deep swamp of bodily waste.\n" +
		"In front of you the soggy ground drops away into a " +
		"canal of diluted excrement flowing almost " +
		"silently into the inky depths of the cavern. Behind " +
		"you, a grime-encrusted ladder ascends to the street " +
		"above.\n\n");
	add_item(({"flow","sewage"}), "The sewage flows slowly, " +
		"almost viscously. Occasionally floating in the " +
		"dark filthy water you make out large shapes: " +
		"driftwood, or some other debris perhaps, bobbing " +
		"gently like small islands in a froth of scum.\n");
	add_item(({"shape","shapes","island","islands","driftwood",
		"debris"}), "Still to be written - perhaps added to " +
		"base_sewer.c along with flow description.\n");
	add_item(({"froth","scum"}), "Still to be written.\n");
	add_item("ladder", "The ladder is old, rusty and grimy. " +
		"Years of sewage accumulated upon its thin, slimy rungs " +
		"have made it a somewhat treacherous climb...\n");

	add_cmd_item("ladder", "climb", "@@climb_ladder");
	add_cmd_item("ladder", "get", "It is bolted to the wall.\n");

	add_prop(ROOM_I_LIGHT, 10);
	add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_SEWER_DIRECTION, "southeast");

	add_exit("s1", "northeast", 0, 1);
	add_exit("s2", "southeast", 0, 1);
}

public void
climb_ladder()
{
	write("You climb the ladder and emerge in the street " +
		"above.\n");
	say(QCTNAME(this_player()) +
		" leaves climbing the ladder.\n");
//    this_player()->move_living("/w/erane/workroom");
	return;
}

