#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Beggar and Wayfarer");
    set_long("This is a small intersection between the heavily travelled "+
      "Wayfarer Boulevard and Beggar's Alley, so named for the abundant "+
      "number of beggars walking its unpaved surface. There are crowded "+
      "buildings all along this intersection, but the ones to the south, "+
      "in Beggars' Alley, look particularly cramped and ramshackle. A "+
      "darkened building in the north catches your eye, while to the "+
      "southwest lies Caravan Lot, filled to capacity with the wagons and "+
      "animals of travelling merchants. Refuse litters the ground here.\n");

    add_item(({ "intersection" }),
      "Wayfarer Boulevard is paved in worn grey cobbles while Beggar's "+
      "Alley is just packed down earth.\n");

    add_item(({ "refuse" }),
      "It's soooo smelly that you can't get close enough to get a good look!\n");

    add_item(({ "darkened building", "building" }), "A shadowed building "+
      "built from stone. A sign hangs out before it.\n");

    add_item("sign", "@@sign");

    add_cmd_item("sign", "read", "@@sign");

    add_exit(CVAN + "wayfar/s4", "west");
    add_exit(CVAN + "delivery/caravan_office", "north");
    add_exit(CVAN + "wall_wayfar", "east");
    add_exit(CVAN + "beggar/s1", "south");

    reset_room();
}

string
sign()
{
    return "The Caravan District delivery office.\n";
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
