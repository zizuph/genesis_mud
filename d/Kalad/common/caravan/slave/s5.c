#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void
create_cvan_room()
{
    set_short("Slave market");
    set_long("You've reached yet another section of the Slave Market, from "+
      "here you can see several dirt paths leading away in different "+
      "directions. The paths to the west and north lead to other sections "+
      "of the compound. The slightly larger path leading to the northwest "+
      "leads to the center of the Slave Market, there you can see a large "+
      "wooden platform, behind which is a small nondescript building. "+
      "Directly in front of you, what you had mistaken as a small building "+
      "is in fact a large cage. Refuse litters the ground here.\n");

    add_item(({ "large wooden platform", "wooden platform", "platform" }),
      "Its been raised five feet above the ground by wooden stilts.\n");

    add_item(({ "building" }),
      "A small, unaddorned wooden building just to the north of the large "+
      "platform.\n");

    add_item(({ "large cage", "cage" }),
      "It is at least twenty feet wide, and the front is open to the dirt "+
      "pathway, but is covered with rusty iron bars. Inside you think you "+
      "see some figures moving around.\n");

    add_item(({ "refuse" }),
      "The remnants of animal droppings as well as a few human droppings.\n");

    add_exit(CVAN + "slave/s2", "west");
    add_exit(CVAN + "slave/s6", "northwest");
    add_exit(CVAN + "slave/s4", "north");
    add_exit(CVAN + "slave/s5a", "in");

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
