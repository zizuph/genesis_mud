#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Caravan lot");
    set_long("You are travelling along a narrow muddy path in the Caravan Lot. "+
      "To the west you can see a large intersection of several paths while "+
      "eastward this path continues to another section of the lot. Crowded "+
      "wagons line the path to the north and south. Animal refuse litters "+
      "the ground here.\n");

    add_item(({ "wagons" }),
      "Many colorful wagons can be seen, each with their individual merchant- "+
      "symbol displayed on the side. Such a profusion of colors is nearly "+
      "overwhelming.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many pack animals brought here by "+
      "the merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s9", "west");
    add_exit(CVAN + "lot/s11", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "animal_merchant");
	ob1->move_living("M",TO);
    }
}
