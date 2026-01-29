/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("An old deserted street");
        set_long(BS(
           "You are in an old ruined street of Xak Tsaroth deep underground in"
	 + " a huge cavern. The buildings"
	 + " are in pretty good shape considering the stresses the cataclysm"
	 + " must have placed on them though many of the walls are leaning"
	 + " dangerously. The street drops away to the west down a steep"
	 + " cliff face which is overgrown with many vines. Water flows"
	 + " through here from the marsh lands above ground and flows"
	 + " over the edge and down the cliff face into the darkness below."
	 + "", 70));

	add_exit(DDIR + "highstreet2.c", "north", 0);

	add_item(({"water", "cliff", "vine", "vines", "cliff face"}), "@@vine");

	INSIDE
        DARK
}

init()
{
	::init();
	ADA("climb");
}

climb(str)
{
	NF("Climb what? climb down?\n");
	if (str != "cliff" && str != "vine" && str != "vines" && str != "down")
		return 0;
	if (TP->query_skill(SS_CLIMB) < 25)
	{
		write(BS("You start to climb down the vines but suddenly you"
		 + " lose your grip and fall all the way to the bottom!"
		 + " You slam into the ground with a bonecrushing sound.", 70));
		SAY(" trys to climb down the cliff face but loses his grip on"
		 + " a vine and falls down into the darkness below. You hear a"
		 + " sickening bonecrushing sound as he hits the ground below.");
		TP->move_living("M", DDIR + "vinebottom.c", 1);
		TP->reduce_hit_point(1000);
		if (TP->query_hp() <= 0)
        			TP->do_die(this_object());
		return 1;
	}
	write(BS("You skillfully climb down the cliff face using the vines"
	 + " for handholds. You climb down through the roof and into an old building"
	 + "", 70));
	SAY(" skillfully climbs down the cliff face.");
	TP->move_living("M", DDIR + "vinebottom.c", 1);
	return 1;
}

vine()
{
	write(BS("Water cascades down the cliff face through the vines. You think"
	 + " you could maybe climb down that cliff face using the vines"
	 + " but it would be very slippery and probably quite dangerous"
	 + " if you aren't a good climber.", 70));
	return "";
}
