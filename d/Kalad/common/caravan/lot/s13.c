#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Caravan lot");
    set_long("You've reached the end of this large and muddy pathway. "+
      "The rest of the path leads away towards the northwest, while lined "+
      "all along it are crowded wagons of myriad descriptions. A particularly "+
      "unusual wagon to the south attracts your attention. Animal refuse "+
      "litters the ground here.\n");

    add_item(({ "crowded wagons", "wagons" }),
      "Many brightly painted wagons are visible, each with its individual "+
      "merchant-symbol. Such a profusion of color nearly overwhelms you.\n");

    add_item(({ "unusual wagon", "wagon" }),
      "It looks like any of the other wagons surrounding you. What catches "+
      "your attention about it are the somber colors it has been painted "+
      "with. Its dark blue and grey paints make it strikingly different "+
      "from the many cheerfully colored wagons around it.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings left behind by the many pack animals brought here by "+
      "the travelling merchants.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s9", "northwest");
    add_exit(CVAN + "lot/s16", "south");

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
