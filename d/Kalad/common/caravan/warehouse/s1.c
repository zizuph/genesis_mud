#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Warehouse lane");
    set_long("You are walking along Warehouse Lane, so named because "+
      "warehouses line the entire length of the street. West of here lies the "+
      "intersection of this road with the heavily travelled Caravan Street. "+
      "Large wooden warehouses lie to the north and south while Warehouse "+
      "Lane continues to the east. Refuse litters the ground here.\n");

    add_item(({ "warehouse lane", "road" }),
      "The street surface is only packed earth, and is littered with refuse.\n");

    add_item(({ "large wooden warehouses", "large warehouses", "wooden warehouses", "warehouses", "warehouse" }),
      "The buildings rise to a height of two stories, that combined with the "+
      "fact that each building is dozens of feet wide results in a huge "+
      "amount of storage space. It looks like you might be able to go "+
      "north and south towards them.\n");

    add_item(({ "refuse" }),
      "A wide variety of trash can be seen, bits and pieces of scrap metal, "+
      "discarded pieces of wood and the droppings of many animals.\n");

    add_exit(CVAN + "caravan/s4", "west");
    add_exit(CVAN + "warehouse/s2", "east");

    add_cmd_item(({ "north", "north" }), "go", "@@go");
    add_cmd_item(({ "south", "south" }), "go", "@@gone");
}

string
go()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("north");
    TP->move_living("north towards the warehouse", CVAN + "warehouse/yard1");
    return "The air doesn't smell too pleasant here.\n";
}

string
gone()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("south");
    TP->move_living("south towards the warehouse", CVAN + "warehouse/yard2");
    return "The air doesn't smell too pleasant here.\n";
}
