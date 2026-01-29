#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Beggar's alley");
    set_long("You are now travelling along Beggar's Alley where many "+
      "homeless are said to dawdle. To the north you can see a large "+
      "intersection, while to the west the crowded stalls of the Caravan "+
      "Lot are visible. Cramped buildings line the road to your east, "+
      "stretching south since they line Beggar's Alley. Animal refuse "+
      "litters the ground here.\n");

    add_item(({ "caravan lot", "lot" }),
      "You see a large, muddy field where travelling merchants along with "+
      "their retinues of laborers and pack animals are.\n");

    add_item(({ "buildings" }),
      "The structures are all built of wood, that looks quite weatherworn "+
      "and in need of repair. They probably serve as housing for some of "+
      "the poorer residents of the Caravan district.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Peering intently at the animal feces, which comes from a variety of "+
      "animals, you deduce that they originate from the many animals in the "+
      "Caravan Lot.\n");

    add_exit(CVAN + "beggar_wayfar", "north");
    add_exit(CVAN + "lot/s7", "west");
    add_exit(CVAN + "beggar/s2", "south");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "obeg");
	ob1->move_living("M", TO);
    }
}
