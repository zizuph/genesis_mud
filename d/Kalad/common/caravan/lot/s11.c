#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Caravan lot");
    set_long("You are travelling along a muddy path in the Caravan Lot. "+
      "Large, muddy pathways lead towards the west and south to different "+
      "areas of the lot. Crowded wagons line the path. Animal refuse litters "+
      "the ground here.\n");

    add_item(({ "wagons" }),
      "Many colorful wagons can be seen, each with its individual merchant - "+
      "symbol. Such a bright profusion of colors is nearly overwhelming.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many pack animals brought here by "+
      "the travelling merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s10", "west");
    add_exit(CVAN + "lot/s14", "south");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "wepmerchant");
	ob1->move_living("M", TO);
    }
}
