#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("West Entrance to Caravan Lot");
    set_long("You've reached the western entrance of the Caravan Lot. "+
      "West from here is the way out of the Caravan Lot, while further east "+
      "lies the rest of the Lot. Many crowded wagons lie to the north and "+
      "south. Animal refuse litters the ground here.\n");

    add_item(({ "wagon", "wagons" }),
      "They are all colorfully decorated in their individual merchant symbols. "+
      "You can barely take in such a profusion of colors.\n");

    add_item(({ "symbol", "symbols" }), "Most of them are obvious merchant "+
      "icons, such as coins, flags, etc.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many animals brought here by the "+
      "travelling merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "caravan/s2", "west");
    add_exit(CVAN + "lot/s5", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard");
	ob1->arm_me();
	ob1->move_living("M", TO);
    }
}
