#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("House");
    set_long("This is the inside of a small, cozy house. Contrary to "+
      "outside appearances, the interior of this building is quite "+
      "comfortable. An iron stove is near the back of this room, probably "+
      "used to cook food. A small bed lies on one side wall while a clothes "+
      "dresser is opposite of it. Glass windows look out onto the street.\n");

    add_item(({ "iron stove", "stove" }), "An ancient-looking stove, its "+
      "probably been in use for the past few decades. However it still "+
      "looks serviceable.\n");

    add_item(({ "small bed", "bed" }), "A cozy little bed, just looking at it "+
      "makes you feel sleepy.\n");

    add_item(({ "clothes dresser", "dresser" }), "A large wooden dresser, "+
      "where many clothes and other items are kept.\n");

    add_item(({ "glass windows", "glass window", "window", "windows" }), "Looking "+
      "out you can see Wall Street.\n");

    add_exit(CVAN + "wall/s1", "out");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "okguard");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }
}
