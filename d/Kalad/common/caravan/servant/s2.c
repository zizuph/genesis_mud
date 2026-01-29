#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Servant street");
    set_long("You are walking along a narrow street between buildings "+
      "that are so tightly packed that it seems they may fall upon you at "+
      "any moment. Westward, past the crowded buildings of this road, you "+
      "can see an intersection. Refuse litters the street.\n");

    add_item( ({ "street" }),
      "This street is extremely narrow, varying in width from as little as "+
      "ten feet to as wide as fifteen feet in some places.\n");

    add_item( ({ "buildings", "building" }),
      "Most of the buildings aside the road are wooden. The majority of "+
      "them show the harsh effects of time and weather, that along with the "+
      "poverty of its inhabitants leaves the buildings in a poor shape.\n");

    add_item( ({ "intersection" }),
      "It seems to be a crossing of this road with another one.\n");

    add_item( ({ "refuse" }),
      "Looking more closely at the filth, you distinguish both human and "+
      "animal feces.\n");

    add_exit(CVAN + "chains_serv", "west");
    add_exit(CVAN + "servant/s3", "east");
}

void
init()
{
    ::init();
    write("The air smells of urine and feces.\n");
}
