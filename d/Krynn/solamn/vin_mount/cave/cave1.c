/* Terminator started this,
 * Aridor, 11/94
 *
 * Updated for cave expansion.
 *
 * Mortis 10.2006
 */

#include "../local.h";

inherit CAVE_BASE

#include <macros.h>;

void
create_vin_mount_room() 
{
	SHORT("Cave entrance");
	LONG("You are in a really disgusting smelling cavern.  You think that "
	+ "you can hear noises farther in, but you are not sure. The dim torches "
	+ "on the walls light the way for you.  To your west, on the ground near "
	+ "the rock, you can make out a little sunlight filtering in.\n");

    ITEM(({"rock"}), "Right next to the rock to your west you can "
	+ "see light on the ground. There is a narrow opening which you might be "
	+ "able to squeeze through to get outside.\n");
    ITEM(({"opening","light"}), "Light from outside is coming through the "
	+ "opening.\n");
    ITEM("outside", "You cannot see the outside from here.\n");
    ITEM(({"torches","torch"}), "There are lit torches affixed to the "
	+ "wall.\n");
    
    CMD(({"out", "under rock", "under the rock", "through", "through opening",
	""}), ({"squeeze", "out"}), "@@squeeze_out@@");
    CMD(({"noises", "to noises", "to noise", "noise"}), "listen", "There are "
	+ "faint, gruff voices to be heard coming from the depths of the cave to "
	+ "your east.\n");

	EXIT(CAVE + "cave01", "east", 0, 0);
}

int
squeeze_out() 
{
    write("You squeeze underneath the rock.\n");
    say(QCTNAME(TP) + " squeezes through underneath the rock.\n");
    TP->move_living("M", ROOM + "road6", 1, 0);
    say(QCTNAME(TP) + " arrives from under the rock.\n");

    return 1;
}
