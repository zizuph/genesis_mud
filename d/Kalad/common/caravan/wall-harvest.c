#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Wall and Harvest");
    set_long("This large intersection is where two busy roadways, Wall "+
      "Street and Harvest Way, cross paths. From here Wall Street stretches "+
      "northward deeper into the Caravan district, and towards the "+
      "Tradesmen's district in the south. Harvest Way heads west from here, "+
      "acting as an informal boundary between the Caravan and Tradesmen's "+
      "districts. Many buildings line the sides of the intersection, except "+
      "for the eastern side, which is dominated by the massive city walls "+
      "of Kabal. All manner of refuse litters the ground here.\n");

    add_item(({ "intersection", "roadways" }),
      "Both streets are paved in slate-grey cobblestones that look worn "+
      "and cracked from heavy use, though still in good condition for such "+
      "a heavily-travelled crossroads.\n");

    add_item(({ "buildings" }),
      "Most of the structures are wooden, and are tightly packed along the "+
      "roadside. They are a mixture of shops and homes, with the shops most "+
      "likely catering to the needs of wandering travellers. The buildings "+
      "appear a bit weathered, just like the roadways, but are still in "+
      "good shape.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "Looking at the wall closer you note the high-grade stone that it was "+
      "constructed from. Such high quality rock could only have come from "+
      "the great Hespyre mountains, which lie east of Kabal. The city walls "+
      "themself rise to a height of thirty feet and from all inspections "+
      "appear very solid. Clearly, the walls present a near insurmountable "+
      "barrier to any invading force.\n");

    add_item(({ "refuse" }),
      "Discarded pices of trash lie across the street surface, bits and "+
      "pieces of scrap metal, useless fragments of wood and even a beggar "+
      "or two.\n");

    add_exit(CVAN + "wall_warehouse", "north");
    add_exit(CVAN + "harvest/s4", "west");
    add_exit(TRADE + "wall/wall11", "south");

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
