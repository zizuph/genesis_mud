#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of a road and Harvest");
    set_long("You are travelling along Harvest Way where crowded buildings "+
      "line the street to the north and south, while a large intersection "+
      "lies to the west. Between two such buildings in the south is a small "+
      "road. Animal refuse litters the ground here.\n");

    add_item(({ "harvest way", "street" }),
      "The roadway is paved in slate-grey cobblestones that look worn and "+
      "slightly cracked from heavy use.\n");

    add_item(({ "buildings" }),
      "Small wooden structures that look to be a mixture of shops and homes.\n");

    add_item(({ "small road", "road" }),
      "A small street paved in cobblestones that heads south into the "+
      "Tradesmen's district.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Peering closer at the filth you distinguish the droppings of several "+
      "types of animals, with those of horses and oxen being the most "+
      "prominent.\n");

    add_exit(CVAN + "caravan-harvest", "west");
    add_exit(TRADE + "tsquare/hc2", "south");
    add_exit(CVAN + "harvest/s3", "east");

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
