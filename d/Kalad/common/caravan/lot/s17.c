#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Master Trader's Wagon");
    set_long("You've entered a surprisingly large and comfortable wagon. "+
      "The wagon's furnishings are quite extravagant, seemingly fit for "+
      "a king, or even a king of kings. Fine, intricately woven carpets "+
      "grace the burnished wood floor. The walls of the wagon are richly "+
      "appointed with delicate and rare paintings. On the side opposite "+
      "you is a large ornate desk, behind which is a high-backed gold-lined "+
      "chair.\n");

    add_item(({ "carpets" }),
      "Thick, exotic floor coverings. Just from a glance you can tell they "+
      "are quite expensive.\n");

    add_item(({ "floor" }),
      "Little of the floor can be seen, since most of it is covered by the "+
      "carpets.\n");

    add_item(({ "paintings" }),
      "Portraits so rare that even you, an experienced adventurer have never "+
      "seen the likes of them. All you can fathom is their priceless beauty.\n");

    add_item(({ "desk" }),
      "Crafted from the fine-grained redwood trees of the Hespyre mountains, "+
      "not only is it beautiful to behold, but built to last.\n");

    add_item(({ "chair" }),
      "A chair so large it looks to have more akin to a throne then a simple "+
      "object to sit on, it commands your respect.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s14", "north");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "mtrader");
	ob1->move_living("M", TO);
    }
}
