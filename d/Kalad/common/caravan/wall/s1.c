#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wall street");
    set_long("You are walking along Wall Street in the Caravan district. "+
      "Glancing to the west you can see crowded buildings lining the "+
      "street, while to the east stand the massive walls encircling Kabal. "+
      "Unfortunately, you also notice bits of animal refuse lying on the "+
      "ground.\n");

    add_item(({ "street" }),
      "This is a fairly average sized street stretching north and south, "+
      "paved in worn and slightly cracked grey cobbles.\n");

    add_item(({ "walls", "massive walls" }),
      "The city walls are made out of the finest stone quarried from the "+
      "Hespyre mountains, lying to the east of Kabal.\n");

    add_item(({ "buildings" }),
      "There are many wooden buildings lining the street. You surmise that "+
      "they serve as housing for the city guards as well as the workers in "+
      "this district. It looks like you could enter one such house to the "+
      "west.\n");

    add_item(({ "house" }), "A small home, cramped in among the other crowded "+
      "buildings lining the western side of the road.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Only a few animal feces can be seen, and these few droppings have "+
      "been swept to the gutters of the street.\n");

    add_exit(CVAN + "wall_gate", "north");
    add_exit(CVAN + "wall_wayfar", "south");

    add_cmd_item(({ "west", "house" }), "enter", "@@enter");
    add_cmd_item("house", "enter", "@@enter");
}

string
enter()
{
    write("You open the door to the house.\n");
    set_dircmd("house");
    TP->move_living("into the house", CVAN + "wall/house");
    return "You close the door behind you.\n";
}
