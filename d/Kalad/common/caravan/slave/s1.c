#include "../default.h"
inherit CVAN_ROOM;

void reset_room();

void
create_cvan_room()
{
    set_short("Dirt intersection");
    set_long("You find yourself at a point where two dirt paths meet. "+
      "Gazing around you can see that one dirt path heads north from here, "+
      "while another travels eastward. Drab-looking buildings line the "+
      "intersection to your west and south. Right in front of you, where "+
      "there is a break in the fence surrounding a collection of buildings, "+
      "you can see an entrance. Refuse litters the ground here.\n");

    add_item(({ "buildings" }),
      "Small, one-story wooden structures that appear to be abandoned.\n");

    add_item(({ "fence" }),
      "A sturdy-looking wooden fence that surrounds a collection of "+
      "buildings to your northeast. The fence stretches out to the north "+
      "and east from here.\n");

    add_item(({ "collection" }),
      "Since you are right by the entrance you peer through the wooden "+
      "gates into the compound. You can make out a few squat, one-story "+
      "structures and a large, raised platform near the center of the "+
      "compound.\n");

    add_item(({ "wooden gates", "gates" }),
      "It blocks the entrance to the northeast, however it is currently "+
      "open.\n");

    add_item(({ "entrance" }),
      "A dirt-covered path, blocked by wooden gates, that leads northeast "+
      "into the compound.\n");

    add_item(({ "refuse" }),
      "The filthy and disgusting remnants of animal droppings and even a "+
      "few human droppings.\n");

    add_exit(CVAN + "servant/s1", "north");
    add_exit(CVAN + "slave/s2", "northeast");
    add_exit(CVAN + "chains/s3", "east");

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
