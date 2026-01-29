#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit STD("room");

#define DAMAGE 150
#define HARD_TO_CLIMB 30

public void
dark_dom(void)
{
    set_long("You find yourself at the bottom of a small "+
	"shaft. There is no ceiling here, at least none that you can see "+
	"for yawning above you like some horrible mouth is a gigantic hole. "+
	"A dark passage heads east from here.\n");

    add_item(({"shaft","small hole","hole"}), "The small shaft leads apparently to " +
    "somewhere above and abit to the west.\n");

    add_exit(P_WATERDEEP_CASTLEWARD +"underm/u50", "up", "@@climb", 3);
    add_exit("u8", "east");
}

public int
climb(void)
{
    if (TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
    {
	write("You slip while climbing the sheer rock face and fall down.\n");
	write("You slam into a group of stalagmites!\n");
	say(QCTNAME(TP) + " fell down while trying to climb the rock "+
	    "face and slammed into some stalagmites.\n");

	TP->heal_hp(-DAMAGE);

	if (TP->query_hp() < 1)
	    TP->do_die(TO);

	return 1;
    }

    write("You manage to scale the rock face.\n");
    say(QCTNAME(this_player()) + " manages to scale the rock face.\n");
    return 0;
}
