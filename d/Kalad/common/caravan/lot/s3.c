#include "../default.h"
inherit CVAN_ROOM;

#define LABOR	(NPC + "clwork")

object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    add_prop(OBJ_I_HAS_FIRE, 1);

    set_short("Labourers' Tent in Caravan Lot");
    set_long("You enter a large and enclosed tent, the sleeping quarters "+
      "for the merchants' labourers. Here you see rows upon "+
      "rows of straw pallets, along with a few scattered cooking fires. "+
      "You wonder at first how fires are possible without suffocating in "+
      "here, then you notice the opening at the top of the tent, where "+
      "most of the smoke is leaving through. There is a small opening in "+
      "the tent flap to the west.\n");

    add_item(({ "straw pallets", "pallets" }),
      "Uncomfortable looking sleeping pallets, probably compounded by the "+
      "legions of lice crawling through it.\n");

    add_item(({ "cooking fires", "fires", "cooking fire", "fire" }),
      "Small, depressing-looking fires, barely hot enough to cook a decent "+
      "meal with.\n");

    add_item(({ "smoke" }), "It is thick, dark and oily. You see a lot of "+
      "it rising from the many fires in this tent.\n");

    add_item(({ "top" }), "The top of the tent lies some thirty feet up, the "+
      "constant fires within this tent have stained it black with soot.\n");

    add_item(({ "opening" }), "A large ten foot wide hole has been cut at "+
      "the top of the tent to allow smoke to leave it.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s2", "west");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(LABOR);
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(LABOR);
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(LABOR);
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(LABOR);
	ob4->move_living("M",TO);
    }

    if(!ob5)
    {
	ob5 = clone_object(LABOR);
	ob5->move_living("M",TO);
    }

    if(!ob6)
    {
	ob6 = clone_object(LABOR);
	ob6->move_living("M",TO);
    }
}
