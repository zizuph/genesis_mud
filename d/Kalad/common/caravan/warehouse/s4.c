#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Warehouse lane");
    set_long("You are walking along Warehouse Lane, so named because of the "+
      "large wooden warehouses lining the entire length of the road. Two such "+
      "buildings lie just to the north and south. Eastward lies the intersection "+
      "of this street with the heavily travelled Wall Street, while Warehouse "+
      "Lane continues to the west. Refuse litters the ground here.\n");

    add_item(({ "warehouse lane", "road", "street" }),
      "It is nothing more than a large dirt pathway.\n");

    add_item(({ "large wooden warehouses", "large warehouses", "wooden warehouses", "warehouses", "buildings", "building" }),
      "They are wooden structures that reach a height of two stories and are "+
      "dozens of feet across. These two factors combine to create a massive "+
      "amount of storage space for a myriad number of trade goods. It looks "+
      "like you might be able to go north and south towards them.\n");

    add_item(({ "refuse" }),
      "A variety of trash can be seen, ranging from bits and pieces of scrap "+
      "metal to large amounts of animal droppings.\n");

    add_exit(CVAN + "warehouse/s3", "west");
    add_exit(CVAN + "wall_warehouse", "east");

    add_cmd_item(({ "north", "north" }), "go", "@@go");
    add_cmd_item(({ "south", "south" }), "go", "@@gone");
}

string
go()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("north");
    TP->move_living("north towards the warehouse", CVAN + "warehouse/yard5");
    return "The air doesn't smell too pleasant here.\n";
}

string
gone()
{
    write("You walk into the warehouse yard.\n");
    set_dircmd("south");
    TP->move_living("south towards the warehouse", CVAN + "warehouse/yard6");
    return "The air doesn't smell too pleasant here.\n";
}
