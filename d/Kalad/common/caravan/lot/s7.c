#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Eastern Entrance into Caravan Lot");
    set_long("You've reached the eastern side of the Caravan Lot. From here "+
      "an exit out of the lot lies just to the east, where lies Beggar's "+
      "Alley. Obviously there isn't much traffic on this side of the lot. "+
      "The muddy path you are standing on continues westward, deeper into "+
      "the crowded Caravan Lot. Many wagons line the path to the north and "+
      "south. Animal Refuse litters the ground here.\n");

    add_item(({ "wagons" }),
      "Crowded wagons can be seen all over, each with its individual "+
      "merchant-symbol. All the wagons are brightly decorated, such a "+
      "profusion of colors nearly overwhelms you.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings of the many pack animals brought here by the "+
      "travelling merchants and their retinues.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s6", "west");
    add_exit(CVAN + "beggar/s1", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard");
	ob1->arm_me();
	ob1->move_living("M", this_object());
    }
}
