#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Caravan and Harvest");
    set_long("This is the intersection of Caravan Street and Harvest Way. "+
      "To the north lies the Caravan district, while south is the Tradesmen's "+
      "district. Crowded buildings line the entire intersection, while further "+
      "southwest along Caravan Street, a massive circular structure, the "+
      "gladiatorial arena of Kabal, is visible. Animal refuse litters the "+
      "intersection.\n");

    add_item(({ "intersection", "caravan street", "harvest way" }),
      "Both roadways are paved in slate-grey cobblestones that look worn "+
      "and slightly cracked, though still in good condition for such heavily "+
      "travelled roads.\n");

    add_item(({ "buildings" }),
      "Small wooden structures, they probably serve the many travellers that "+
      "use Caravan Street and Harvest Way.\n");

    add_item(({ "massive circular structure", "circular structure", "structure", "arena" }),
      "Little detail can be made out from here, save for the immense size "+
      "of the structure.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Examining the filth further, you discern the droppings of several "+
      "types of animals, with horses and oxen being most prominent.\n");

    add_exit(CVAN + "harvest/s2", "west");
    add_exit(CVAN + "caravan/s4", "northeast");
    add_exit(CVAN + "road1-harvest", "east");
    add_exit(CENTRAL + "caravan/s1", "southwest");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "cmilitia");
	ob1->move_living("M", TO);
    }
}

int
block()
{
    write("The way is blocked by a barricade.\n");
    return 1;
}
