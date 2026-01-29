#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Harvest way");
    set_long("You are travelling along Harvest Way. Visible to the west "+
      "and east are two large intersections. Lining the street to the north "+
      "and south are many crowded buildings. Far to the south, rising just "+
      "above the tops of the buildings is a massive circular structure, the "+
      "Gladiatorial Arena of Kabal. Animal refuse litters the ground here.\n");

    add_item(({ "harvest way", "street" }),
      "The road is paved in slate-grey cobblestones that look worn and "+
      "slightly cracked. However, the street is in fairly good condition "+
      "considering the amount of traffic that uses it daily.\n");

    add_item(({ "buildings" }),
      "Small wooden structures, they probably serve the many farmers that "+
      "use Harvest Street to get back to the western farmlands.\n");

    add_item(({ "massive circular structure", "circular structure", "structure", "arena" }),
      "Little detail can be made out from this point, save the immense size "+
      "of the building.\n");

    add_item(({ "animal refuse" }),
      "It looks to be the droppings of several types of animals, probably "+
      "coming from the ones brought into Kabal by farmers.\n");

    add_exit(CVAN + "high-harvest", "west");
    add_exit(CVAN + "chains_harvest", "east");
}
