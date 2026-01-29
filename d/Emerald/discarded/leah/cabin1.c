inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/sys/cmdparse.h"

void create_room()
{
	add_prop(ROOM_I_INSIDE,1);
	set_short("Inside yellow cabin");
	set_long("   The walls of this small home are a soft yellow. It "+
		"is sparsely furnished, leading you to assume that "+
		"either a family is moving out, or one is moving in. "+
		"Looking around, the only furniture you see is a old "+
		"looking table. A quick chill goes down your spine "+
		"causing you to want to leave immediately!!\n\n" + 
		"@@exit_desc@@");

	add_item(({"furniture", "table", "old table"}), "This table is "+
		"scratched and battered, and has seen better days.\n");
	add_item(({"walls", "yellow walls"}), "The dust-streaked walls "+
		"of this cabin are painted with a soft yellow, apparently "+
		"the manner of elves.\n");
	add_item(({"aura", "aura of magic"}), "The traditional elven "+
		"aura of magic.\n"); 

	add_exit(VILLAGE_DIR + "alley1", "south", 0);
	add_exit(VILLAGE_DIR + "c1", "north", "@@north_block@@");
	set_noshow_obvious(1);
}

int
north_block()
{
    if (sizeof(FIND_STR_IN_OBJECT("yellow rose", this_player())) > 0)
	return 0;
    write("There is no obvious exit north.\n");
    return 1;
}

string
exit_desc()
{
    if (sizeof(FIND_STR_IN_OBJECT("yellow rose", this_player())) > 0)
	return "There are two obvious exits: north, south.\n";
    return "There is one obvious exit: south.\n";
}
