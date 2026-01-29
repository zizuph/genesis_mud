#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Warehouse lane");
    set_long("You are travelling along Warehouse Lane, where large wooden "+
      "warehouses filled with valuable trade goods line the entire length "+
      "of the road. Two such buildings lie just north and south of here. "+
      "Refuse litters the ground here.\n");

    add_item(({ "warehouse lane", "road" }),
      "It is nothing more than a large dirt pathway.\n");

    add_item(({ "large wooden warehouses", "wooden warehouses", "warehouses", "buildings", "large warehouses", "warehouse", "building" }),
      "They are large structures, rising to a height of two stories and "+
      "stretching dozens of feet across. These two factors combine to create "+
      "a huge amount of storage space. It looks like you might be able to "+
      "go north and south towards them.\n");

    add_item(({ "refuse" }),
      "A variety of trash can be seen, bits and pieces of scrap metal, "+
      "discarded pieces of wood, and the droppings of many types of animals.\n");

    add_exit(CVAN + "warehouse/s2", "west");
    add_exit(CVAN + "warehouse/s4", "east");

    add_cmd_item(({ "north", "north" }), "go", "@@go");
    add_cmd_item(({ "south", "south" }), "go", "@@gone");
}

string
go()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("north");
    TP->move_living("north towards the warehouse", CVAN + "warehouse/yard3");
    return "The air doesn't smell too pleasant here.\n";
}

string
gone()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("south");
    TP->move_living("south towards the warehouse", CVAN + "warehouse/yard4");
    return "The air doesn't smell too pleasant here.\n";
}
