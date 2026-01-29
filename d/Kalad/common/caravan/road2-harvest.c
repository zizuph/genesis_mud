#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of a road and Harvest");
    set_long("You are walking along Harvest Way, where crowded buildings "+
      "line the street to the north and south. Between two such buildings "+
      "in the south is a small road, heading out of this district, the "+
      "Caravan district, into the adjacent Tradesmen's district. Animal "+
      "refuse litters the ground here.\n");

    add_item(({ "harvest way", "street" }),
      "The roadway which stretches west and east is paved in slate-grey "+
      "cobblestones. The pavement appears worn and slightly cracked from "+
      "heavy traffic.\n");

    add_item(({ "buildings" }),
      "Small wooden structures line the streets. The buildings seem to be a "+
      "mixture of shops and homes, and you surmise that the shops get the "+
      "majority of their income from the many farmers that travel along this "+
      "thouroughfare.\n");

    add_item(({ "small road", "road" }),
      "A small avenue paved in cobblestones heading south.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Examining the filth closer you discern the droppings of several "+
      "different types of animals, with horses and oxen being the most "+
      "prominent.\n");

    add_exit(CVAN + "harvest/s3", "west");
    add_exit(TRADE + "tsquare/hc1", "south");
    add_exit(CVAN + "harvest/s4", "east");

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
