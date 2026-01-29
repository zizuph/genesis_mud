#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Chains and Harvest");
    set_long("This t-intersection is where the gloomy Street of Chains "+
      "meets with the heavily travelled Harvest Way, also known as Farmer's "+
      "Way because many farmers use the roadway to travel to the farms that "+
      "lie west of Kabal. Crowded buildings line the entire intersection. "+
      "Rising in the south past several buildings is a massive circular "+
      "structure, the Gladiatorial Arena of Kabal. Animal Refuse litters "+
      "the ground here.\n");

    add_item(({ "street of chains" }),
      "It appears to have been paved in cobblestones at one point in time, "+
      "now however it is little more than a large dirt pathway.\n");

    add_item(({ "harvest way", "farmer's way", "roadway" }),
      "This cobblestoned street, which heads west and east from here, is a "+
      "main thoroughfare in the heart of Kabal. Due to heavy traffic, the "+
      "street's cobbles are worn and slightly cracked, though still in good "+
      "shape. Another side effect of the street being used by farmers is "+
      "the animal refuse that litters the intersection.\n");

    add_item(({ "buildings" }),
      "You see a myriad number of wooden structures lining both roadways. "+
      "These buildings probably serve the many farmers that use Harvest "+
      "Way.\n");

    add_item(({ "massive circular structure", "circular structure", "massive structure", "gladiatorial arena", "arena" }),
      "Little detail can be made out from here, all that can be made out is "+
      "the huge size of the structure. It must be several hundred feet away "+
      "yet it nearly fills your entire vision.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Piles of animal feces are scattered across the intersection, clearly "+
      "coming from the many animals that travel along Harvest Way.\n");

    add_exit(CVAN + "harvest/s1", "west");
    add_exit(CVAN + "chains/s3", "north");
    add_exit(CVAN + "harvest/s2", "east");

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
