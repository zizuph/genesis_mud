#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Harvest way");
    set_long("You are travelling along Harvest Way which stretches to the "+
      "west and east. Crowded buildings lie to the north and south, while "+
      "large intersections can be seen towards the west and east. Just "+
      "visible far to the south is a massive circular structure, the "+
      "gladiatorial arena of Kabal. Animal refuse litters the ground here.\n");

    add_item(({ "harvest way" }),
      "The street is paved in slate-grey cobblestones that look worn and slightly "+
      "cracked, though still in good condition for such a heavily used "+
      "roadway.\n");

    add_item(({ "buildings" }),
      "Small wooden structures, they probably serve the many farmers that use "+
      "Harvest Way.\n");

    add_item(({ "massive circular structure", "circular structure", "structure", "arena" }),
      "Little detail can be distinguished from here, save for the immense "+
      "size of the building.\n");

    add_item(({ "animal refuse", "refuse" }),
      "It looks like the droppings of many types of animals, probably the "+
      "ones brought into Kabal by farmers.\n");

    add_exit(CVAN + "chains_harvest", "west");
    add_exit(CVAN + "caravan-harvest", "east");
}
