#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Cargo Alley and Gateway Lane");
    set_long("You've just reached the T-intersection where Cargo Alley "+
      "meets the larger Gateway Lane. Gateway Lane which is paved with "+
      "cobblestones travels west-east along the northern walls of Kabal. "+
      "To the southwest, past high stone walls, you can see a large "+
      "edifice. Refuse litters the ground.\n");

    add_item( ({ "walls", "stone walls" }),
      "This stone wall, which stretches to the west and south is remarkably "+
      "clear of graffiti or other filth on its surface.\n");

    add_item( ({ "edifice" }),
      "All you can tell from this spot is that the building is very high, "+
      "for you can only see the upper portions of it past the fifteen foot "+
      "wall that surrounds the building.\n");

    add_item( ({ "refuse" }),
      "This is animal refuse left behind by the many animals brought into "+
      "this district by merchants and other travellers. It is quite "+
      "putrid.\n");

    add_exit(CVAN + "gateway/s2", "west");
    add_exit(CVAN + "alley/s1", "south");
    add_exit(CVAN + "gateway/s3", "east");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "cmilitia");
	ob1->move_living("M", TO);
    }
}
