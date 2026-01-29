#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Caravan Lot");
    set_long("You find yourself at the end of the muddy pathway. From "+
      "here the path continues back to the north. Crowded wagons line "+
      "both sides of the pathway. One particularly large wagon catches your "+
      "attention in the south. Animal refuse litters the ground here.\n");

    add_item(({ "crowded wagons", "wagons" }),
      "Many wagons can be seen, each colorfully decorated with its "+
      "individual merchant-symbol. Such a bright profusion of colors is "+
      "nearly overwhelming.\n");

    add_item(({ "large wagon", "wagon" }),
      "A masterfully-designed wagon, its graceful yet strong curves inspires "+
      "a wonder in you about the beauty of shaping wood. It looks like "+
      "you could enter it.\n");

    add_item(({ "wood" }),
      "It looks like it was cut from one of the mighty redwoods in the "+
      "forests of the Hespyre mountains. Clearly this wagon belongs to "+
      "someone of great wealth, and perhaps power.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many pack animals brought here by "+
      "the travelling merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s11", "north");
    add_exit(CVAN + "lot/s17", "south");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }
}
