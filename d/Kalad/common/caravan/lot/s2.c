#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Caravan lot");
    set_long("You've reached another section of the Caravan Lot, from "+
      "here muddy paths lead away to the south and east. A large tent is visible "+
      "to the east. Crowded wagons line both paths. Animal refuse litters "+
      "the ground here.\n");

    add_item(({ "large tent", "tent" }),
      "A massive tent lying just a few dozen feet eastward, many tracks "+
      "lead towards it.\n");

    add_item(({ "tracks" }),
      "Unlike other areas of the lot, there are more human tracks here then "+
      "animal ones.\n");

    add_item(({ "wagons" }),
      "Many wagons can be seen, each with its individual merchant-symbol. "+
      "They are all colorfully decorated, such a profusion of colors is "+
      "nearly overwhelming.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings of the many pack animals brought here by travelling "+
      "merchants and their retinues.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s6", "south");
    add_exit(CVAN + "lot/s3", "east");
}
