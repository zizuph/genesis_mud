inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/sys/cmdparse.h"

void create_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Inside white cabin");
    set_long("   The walls of this small home are a vibrant white. It "+
      "appears fully furnished but covered with a thick layer of dust, "+
      "leading you to assume that whomever once resided here has abandoned it. "+
      "A sharp chill goes down your spine as you wonder what would "+
      "cause them to abandon their home.\n\n" + "@@exit_desc@@");
    add_item(({"walls", "white walls"}), "The dust-streaked walls of this "+
      "cabin are painted with a vibrant white, apparently the manner of elves.\n");
    add_item("dust", "There seems to be years of dust about in here, blanketing "+
      "the floor, the furniture, and even streaking the walls. Your footsteps "+
      "stir the dust up, and you suppress a sneeze.\n");
    add_item(({"aura", "aura of magic"}), "The traditional elven aura of magic.\n"); 

    add_exit(VILLAGE_DIR + "alley3", "south", 0);
    add_exit(VILLAGE_DIR + "c3", "north", "@@north_block@@");
    set_noshow_obvious(1);
}

int
north_block()
{
    if (sizeof(FIND_STR_IN_OBJECT("white rose", this_player())) > 0)
	return 0;
    write("There is no obvious exit north.\n");
    return 1;
}

string
exit_desc()
{
    if (sizeof(FIND_STR_IN_OBJECT("white rose", this_player())) > 0)
	return "There are two obvious exits: north, south.\n";
    return "There is one obvious exit: south.\n";
}
