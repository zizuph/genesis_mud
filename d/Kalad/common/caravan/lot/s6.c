#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Second Small Intersection in Caravan Lot");
    set_long("You've reached a small intersection in the Caravan Lot. Muddy "+
      "paths lead away in several directions. To the west is another small "+
      "intersection, while the paths to the north and east lead to other "+
      "areas of the lot. Crowded wagons line the entire intersection. Animal "+
      "refuse litters the ground here.\n");

    add_item(({ "wagons" }),
      "Many colorful wagons are visible, each with its individual merchant - "+
      "symbol. Such profusion of color is nearly overwhelming.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many pack animals brought here by "+
      "travelling merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s5", "west");
    add_exit(CVAN + "lot/s2", "north");
    add_exit(CVAN + "lot/s7", "east");
}
