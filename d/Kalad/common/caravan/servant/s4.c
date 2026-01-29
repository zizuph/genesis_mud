#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Servant street");
    set_long("You are travelling on Servant Street, a narrow road with "+
      "crowded buildings lining the south side of the street. Between some of "+
      "these buildings is a narrow lane that heads south. Sprawling to the "+
      "north is Caravan Lot, a large muddy field filled to capacity with the "+
      "wagons, pack animals and retinues of travelling merchants. Animal "+
      "refuse litters the ground here.\n");

    add_item(({ "road", "street" }),
      "It looks to have been paved in cobblestones at one point in time. "+
      "However, the road surface is only packed dirt now, with a few "+
      "cobblestones lying here and there, partially covered in dirt.\n");

    add_item(({ "buildings" }),
      "They are crowded structures of wood that look in need of repair, there "+
      "is a gap between some buildings where a narrow lane can be seen heading "+
      "south.\n");

    add_item(({ "caravan lot", "lot", "large muddy field", "muddy field", "field" }),
      "The field is quite large, seemingly capable of holding dozens of "+
      "wagons, along with the merchants that own them, their animals as well "+
      "as many laborers.\n");

    add_item(({ "wagons" }),
      "A myriad of colorful wagons with various merchant-house symbols fills "+
      "the Caravan Lot.\n");

    add_item(({ "pack animals", "animals" }),
      "The most prominent visible are horses, oxen and camels, although a "+
      "few exotic animals can also be seen.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Animal droppings litter the entire roadway, considering the proximity "+
      "of Caravan Lot you surmise that the droppings belong to the many "+
      "animals kept there.\n");

    add_exit(CVAN + "caravan_serv", "west");
    add_exit(CVAN + "warehouse/s2", "south");
    add_exit(CVAN + "servant/s5", "east");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "corpsetaker");
	ob1->move_living("M", TO);
    }
}
