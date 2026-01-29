#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void
create_cvan_room()
{
    set_short("Slave market");
    set_long("You've just reached another section of the slave market, "+
      "several paths lead from here in various directions. Two dirt paths, "+
      "one to the south and another eastward lead to other sections of "+
      "the compound. The dirt path southeast leads to a large, wooden "+
      "platform, behind which is a small nondescript building. Right in "+
      "front of you, what you had mistaken as a small building is in fact "+
      "a large cage. Refuse litters the ground here.\n");

    add_item(({ "platform" }),
      "It has been raised to a height of five feet.\n");

    add_item(({ "building" }),
      "A small, unadorned wooden building that sits just north of the "+
      "platform.\n");

    add_item(({ "large cage", "cage" }),
      "A wooden cage perhaps twenty feet across, peering inside you think "+
      "you can see some figures behind the rusty iron bars.\n");

    add_item(({ "refuse" }),
      "It looks like the remnant of animal droppings as well as some human "+
      "droppings.\n");

    add_exit(CVAN + "slave/s2", "south");
    add_exit(CVAN + "slave/s6", "southeast");
    add_exit(CVAN + "slave/s4", "east");
    add_exit(CVAN + "slave/s3a", "in");

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
