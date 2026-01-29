#include "../default.h"
inherit CVAN_ROOM;

#define STEP	("@@step:/d/Kalad/common/caravan/step")

void
create_cvan_room()
{
    set_short("Small Intersection in Caravan Lot");
    set_long("You have reached a small intersection here in the Caravan "+
      "Lot. Muddy paths lead off in the cardinal directions. To the north "+
      "a particularly strong smell is emanating from a large tent. East, "+
      "west and south of here the muddy paths lead to other sections of the lot. "+
      "Crowded wagons lie along the intersection. Animal refuse litters the "+
      "ground here.\n");

    add_item(({ "large tent", "tent" }),
      "It is probably the largest tent you've ever seen in your life. Clearly "+
      "it is the largest structure in all of the Caravan Lot. Strange noises "+
      "can be heard from it.\n");

    add_item(({ "wagons" }),
      "Many colorful wagons can be seen, each with their individual merchant - "+
      "symbol painted on their sides. Such profusion of color is nearly overwhelming.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings of the many animals brought here by travelling merchants. "+
      "There seems to be more animal waste here then in other parts of the "+
      "lot.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s4", "west");
    add_exit(CVAN + "lot/s1", "north", STEP);
    add_exit(CVAN + "lot/s6", "east");
    add_exit(CVAN + "lot/s9", "south");
}
