#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Chains and Wayfarer");
    set_long("You've just arrived at the intersection of the Street of "+
      "Chains and Wayfarer Boulevard. To the north, visible past a high "+
      "stone wall, is a large and imposing edifice. East from here lies "+
      "another intersection and peering south, you can make out the "+
      "cramped buildings lining the Street of Chains. Animal refuse is "+
      "littered across the ground here.\n");

    add_item(({ "intersection", "street" }),
      "This is where the two streets meet, while the buildings along "+
      "Wayfarer Boulevard are somewhat crowded, the structures aside the "+
      "Street of Chains are packed to capacity.\n");

    add_item(({ "wall", "stone wall" }),
      "It's a large stone wall that stands at least fifteen feet in height "+
      "and stretches to the west and east. Remarkably, there is not one "+
      "mark of graffiti or filth on its surface.\n");

    add_item(({ "edifice" }),
      "Little can be made out of the structure, as most of it is covered "+
      "from view by the high stone wall. All that can be made out is the "+
      "dark grey stone it is constructed from.\n");

    add_item(({ "buildings" }),
      "A variety of buildings can be made out, most of them wooden "+
      "structures around one or two stories in height. You are too far away "+
      "to tell exactly what the purpose of many of the buildings are.\n");

    add_item(({ "refuse", "animal refuse" }),
      "Holding your breath, you take a closer peek at the refuse. It seems "+
      "to be animal droppings left behind by horses and oxen...as you can "+
      "no longer hold your breath you quickly move away.\n");

    add_exit(CVAN + "wayfar/s1", "west");
    add_exit(CVAN + "alley_wayfar", "east");
    add_exit(CVAN + "chains/s1", "south");

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
