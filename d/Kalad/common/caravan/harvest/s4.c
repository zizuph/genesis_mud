#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Harvest way");
    set_long("You are travelling along Harvest Way, which stretches to "+
      "the west and east. Crowded buildings line the street just to the "+
      "north and south, while a large intersection can be seen towards the "+
      "east. Animal refuse litters the ground here.\n");

    add_item(({ "harvest way", "street" }),
      "Examining the road more closely, you see that the slate-grey "+
      "cobblestones it is paved in are worn, and slightly cracked. However, "+
      "the street is still in good condition considering the large amounts "+
      "of traffic that use it daily.\n");

    add_item(({ "buildings" }),
      "Small wooden structures that are a mixture of shops and homes. You "+
      "surmise that the shops gain most of their profit from the many "+
      "farmers that use Harvest Way.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Peering at the filth hesitantly, you distinguish the droppings of "+
      "a myriad number of animals, with horses and oxen being the most "+
      "prominent.\n");

    add_exit(CVAN + "road2-harvest", "west");
    add_exit(CVAN + "wall-harvest", "east");
}
