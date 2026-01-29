#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Street of chains");
    set_long("This darkened street you are walking on is the Street of "+
      "Chains, so named because the lucky individuals due for sale at the "+
      "slave market are held prisoner here, before they head for the "+
      "auction block. Many crowded buildings line the roadside, which heads "+
      "north and also south to a large intersection. Refuse litters the "+
      "street.\n");

    add_item(({ "street" }),
      "The street seems to have once been paved with cobblestones, but "+
      "they have long since been worn away or torn loose. What few cobbles "+
      "left are obscured by the dirt that most of the street is now made "+
      "out of.\n");

    add_item(({ "buildings" }),
      "All the structures are built out of wood and look in need of heavy "+
      "repair.\n");

    add_item(({ "refuse" }),
      "It's so disgusting, you can't quite force yourself to examine it any "+
      "closer than from the other side of the street!\n");

    add_exit(CVAN + "chains/s1", "north");
    add_exit(CVAN + "chains_serv", "south");
}
