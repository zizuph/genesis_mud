#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Center of the Slave Market");
    set_long("This large clearing appears to be the center of the great "+
      "Slave Market of Kabal. In actuality there is nothing 'great' about this "+
      "clearing. This place is nothing more than a large open space that is "+
      "covered with churned mud. The only thing of note is the large "+
      "wooden platform at the center of the clearing, along with a few small "+
      "buildings in the cardinal directions.\n");

    set_time_desc("The clearing is crowded with dozens of people, here "+
      "to purchase slaves.\n", "The clearing contains just a few people, "+
      "hoping to buy slaves for themselves.\n");

    add_item(({ "people" }), "A variety of people can be seen, most of them "+
      "are the servants of nobles, here to purchase slaves for their "+
      "masters and mistresses.\n");

    add_item(({ "large wooden platform", "wooden platform", "platform" }),
      "It's been raised five feet above the ground by small wooden supports. "+
      "This looks like the place where slaves are auctioned and sold.\n");

    add_item(({ "small buildings", "buildings" }),
      "Small wooden structures that appear as if they may collapse at any "+
      "moment. The building to the north looks in slightly better condition "+
      "than the others.\n");

    add_exit(CVAN + "slave/s3", "northwest");
    add_exit(CVAN + "slave/s4", "northeast");
    add_exit(CVAN + "slave/s2", "southwest");
    add_exit(CVAN + "slave/s5", "southeast");
    add_exit(CVAN + "slave/s7", "platform", "@@query_move");

    clone_object(CVAN + "door/wdoor")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard_s");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }
}

query_move()
{
    object *ob;
    int pres, i;

    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if(ob[i]->query_name() == "Guard")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("You are stopped by the guardsman of Kabal.\n");
	say("The guardsman of Kabal stops " + QTNAME(TP) + " from going up to the platform.\n");
    }
    return pres;
}
