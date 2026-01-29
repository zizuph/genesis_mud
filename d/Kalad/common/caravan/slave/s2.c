#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void
create_cvan_room()
{
    set_short("Slave market");
    set_long("This is the first section of the compound, glancing around "+
      "you note several muddy paths leading from here. To the southwest lies "+
      "the exit out of the slave market, while muddy paths to the north and east "+
      "lead to other sections of the compound. There is also a path to the "+
      "northeast that leads to a large, wooden platform beside a nondescript "+
      "building. A few feet from you, what you had mistaken as a small "+
      "building is in fact a large cage. Refuse litters the ground here.\n");

    add_item(({ "exit" }),
      "A small dirt pathway, blocked by wooden gates, that leads southwest "+
      "out of the compound.\n");

    add_item(({ "wooden gates", "gates" }),
      "They block the exit out of the slave market to the southwest.\n");

    add_item(({ "platform" }),
      "A platform that's been raised to a height of five feet.\n");

    add_item(({ "wooden building", "building" }),
      "It's a small, unadorned structure that is just north of the platform.\n");

    add_item(({ "large cage", "cage" }),
      "It is a wooden cage perhaps as wide as twenty feet. Rusty iron bars "+
      "cover the front of the cage, inside you think you can see several "+
      "figures.\n");

    add_item(({ "refuse" }),
      "It looks like the remnants of animal droppings, as well as a few human "+
      "droppings.\n");

    add_exit(CVAN + "slave/s1", "southwest");
    add_exit(CVAN + "slave/s3", "north");
    add_exit(CVAN + "slave/s6", "northeast");
    add_exit(CVAN + "slave/s5", "east");
    add_exit(CVAN + "slave/s2a", "in");

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
