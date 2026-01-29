#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void
create_cvan_room()
{
    set_short("Slave market");
    set_long("You've reached yet another section of the Slave Market, "+
      "several dirt paths lead away from here in various directions. The "+
      "paths to the west and south lead to other areas of the compound. "+
      "A larger path to the southwest leads to the center of the compound "+
      "where there is a large, raised platform, behind which is a small "+
      "nondescript building. What you had mistaken as a large building in "+
      "front of you is in fact a large cage. Refuse litters the ground "+
      "here.\n");

    add_item(({ "dirt paths", "paths", "larger path", "path" }),
      "Regular dirt-covered pathways. Refuse is scattered across their "+
      "surfaces.\n");

    add_item(({ "platform" }),
      "A wooden platform raised to a height of five feet.\n");

    add_item(({ "building" }),
      "A unaddorned wooden building just north of the platform.\n");

    add_item(({ "large cage", "cage" }),
      "A cage built out of wood, perhaps twenty feet across. Behind the "+
      "rusty iron bars covering the front, you think you see several figures "+
      "moving around.\n");

    add_item(({ "refuse" }),
      "The remnants of animal droppings, as well as a few human droppings.\n");

    add_exit(CVAN + "slave/s3", "west");
    add_exit(CVAN + "slave/s6", "southwest");
    add_exit(CVAN + "slave/s5", "south");
    add_exit(CVAN + "slave/s4a", "in");

    reset_room();
}

void
reset_room()
{
    object guard;

    if(!present("guard",TO))
    {
	seteuid(getuid(this_object()));
	guard = clone_object(NPC + "kguard");
	guard->arm_me();
	guard->move(TO);
    }
}
