#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Servant street");
    set_long("You are walking along Servant Street, a road so narrow that "+
      "in some points it is only ten feet wide. The buildings aside the "+
      "street are so tightly packed that a few seem to stretch out over the "+
      "road in a vain attempt to create more room inside them. "+
      "Intersections can be seen to the west and east. To the southeast a "+
      "sturdy-looking wooden fence encircles a collection of buildings. "+
      "Glancing south, you also notice a small dirt path that travels "+
      "alongside the wooden fence, which heads south from here. The rest of "+
      "the fence continues east. Animal Refuse litters the street.\n");

    add_item(({ "servant street", "road", "street" }),
      "The roadway seems to have once been paved with cobblestones, now "+
      "however most of the cobblestones have either been worn away or torn "+
      "out, since the street is mostly packed dirt. The road's width varies "+
      "widely but appears to be about fifteen feet on average.\n");

    add_item(({ "buildings" }),
      "Dark, wooden structures that seem to visibly sag, as if the effects "+
      "of time and weather, and perhaps even the gloomy poverty of its "+
      "inhabitants, weighs down upon them like a physical burden.\n");

    add_item(({ "wooden fence", "fence" }),
      "An ordinary looking fence, it blocks off most of your view of the "+
      "collection of buildings that it surrounds. There doesn't appear to "+
      "be any easy way over it.\n");

    add_item(({ "collection" }),
      "All you can make out from here are a few, squat wooden structures "+
      "and what looks like a raised platform near the center.\n");

    add_item(({ "small dirt path", "dirt path", "small path", "path" }),
      "A narrow, dirt-covered path that travels alongside the fence as it "+
      "heads south.\n");

    add_item(({ "animal refuse", "refuse" }),
      "It looks like the remnants of several kinds of animal feces. The "+
      "refuse covers nearly the entire road.\n");

    add_exit(CVAN + "high_serv", "west");
    add_exit(CVAN + "slave/s1", "south");
    add_exit(CVAN + "chains_serv", "east");
}
