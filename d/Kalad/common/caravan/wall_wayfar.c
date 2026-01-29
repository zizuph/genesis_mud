#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Wall and Wayfarer");
    set_long("You've just reached the intersection of Wall Street and "+
      "Wayfarer Boulevard. Both streets are paved in dark grey "+
      "cobblestones which are worn and slightly cracked. Looking westward "+
      "along Wayfarer Boulevard, you can see another, though smaller, "+
      "intersection. Crowded buildings line the street in all directions. "+
      "There are scattered piles of refuse lying about.\n");

    add_item(({ "intersection", "street", "streets" }),
      "Since both roads are major thouroughfares, the cobbles used to pave "+
      "them are in a somewhat poor shape, although in quite a good "+
      "condition for being so heavily travelled.\n");

    add_item(({ "buildings" }),
      "Most of the structures you can see you believe to be the homes of "+
      "the city's guards and other workers.\n");

    add_item(({ "refuse" }),
      "A variety of trash litters this intersection, in addition to the "+
      "usual animal droppings, there are discarded pieces of wood, metal "+
      "and anything else of little value.\n");

    add_exit(CVAN + "wall/s1", "north");
    add_exit(CVAN + "beggar_wayfar", "west");
    add_exit(CVAN + "wall/s2", "south");

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
