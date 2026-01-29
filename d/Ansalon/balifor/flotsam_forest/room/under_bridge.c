#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

#include "river_drink.h"

#define LAIR "/d/Ansalon/balifor/flotsam_forest/room/troll_lair"
object troll;

void
reset_flotsam_room()
{
    if(!objectp(troll))
    {
	troll = clone_object(FNPC + "troll");
	troll->move(TO);
	LAIR->reset_flotsam_room();
    }
}

create_flotsam_room()
{
    set_short("Under the bridge beside a troll cave");
    set_long("@@long_descr");

    add_item("bridge","You stand underneath a bridge " +
      "at what looks like a troll's lair.\n");
    add_item("shadows","Deep shadows cast by the bridge " +
      "makes this area rather dark.\n");
    add_item(({"scattered bones","bones"}),
      "Many bones of various creatures, ranging from small " +
      "humanoid creatures to goat carcasses litter " +
      "the ground here, marking this area as a lair " +
      "of some nasty creature, probably a troll.\n");
    add_item(({"carcasses","goat carcasses"}),
      "Ha! Those billy goats got what was coming to them!\n");
    add_item(({"cave","lair","troll's lair","hole",
	"troll cave"}),
      "To your east is a hole in a river bank that leads " +
      "into a dark cave, the lair of a troll by looks.\n");

    add_exit(FROOM + "traila","south",0);

    add_cmd_item(({"river","water","from river","water from river"}),
      "drink","@@drink_water");
    add_cmd_item(({"cave","lair","hole"}),"enter",
      "@@enter_cave");

    DARK;

    reset_flotsam_room();
}

int
enter_cave()
{
    if(objectp(troll) && E(troll) == TO)
    {
	write("The river troll is sitting in the way. " +
	  "You can't enter the cave.\n");
	return 1;
    }
    TP->move_living("into the troll's lair",FROOM + "troll_lair",0,0);
    return 1;
}

string
long_descr()
{
    return "You stand underneath a bridge beside " +
    "a swiftly flowing river. The shadow cast by the bridge " +
    "makes it quite dark under here, although not dark " +
    "enough for you not to notice the scattered bones " +
    "of various creatures that mark the lair of a troll. " +
    "To your east you notice the troll's lair, a hole that " +
    "runs into the side of the river bank.\n";
}


