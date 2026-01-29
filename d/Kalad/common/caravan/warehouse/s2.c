#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Warehouse lane");
    set_long("You are travelling along Warehouse Lane, where the entire "+
      "length of the road is lined with warehouses filled with valuable trade "+
      "goods. Between two large warehouses in the north lies a small, narrow "+
      "alleyway. Refuse litters the ground here.\n");

    add_item(({ "warehouse lane", "road" }),
      "It is nothing more than a large dirt pathway.\n");

    add_item(({ "warehouses", "warehouse" }),
      "The buildings are all built of wood and rise to a height of two "+
      "stories and are several dozen feet across. Those two factors combine "+
      "to create a massive amount of storage space.\n");

    add_item(({ "narrow alleyway", "alleyway" }),
      "A shadow filled path that seems to lead away to the north.\n");

    add_item(({ "refuse" }),
      "A variety of trash can be seen, bits and pieces of scrap metal, "+
      "discarded pieces of wood, and the droppings of many kinds of animals.\n");

    add_exit(CVAN + "warehouse/s1", "west");
    add_exit(CVAN + "servant/s4", "north");
    add_exit(CVAN + "warehouse/s3", "east");
}
