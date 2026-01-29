#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Gateway lane");
    set_long("You are travelling along Gateway Lane in the northeastern "+
      "area of the Caravan district. To the north, the massive stone walls "+
      "of Kabal can clearly be seen. Crowded buildings line the street to "+
      "the south. Animal refuse litters the street.\n");

    add_item(({ "stone walls", "walls", "wall" }),
      "These finely crafted walls, made from the finest stone, encircle the "+
      "entire city of Kabal.\n");

    add_item(({ "buildings" }),
      "There are many wooden buildings lining the street. You surmise that "+
      "that they serve as housing for the city guards and other workers in "+
      "this district.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Upon further examination you realize that these are animal "+
      "dropppings left behind by horses and oxen.\n");

    add_exit(CVAN + "gateway/s5", "west");
    add_exit(CVAN + "wall_gate", "east");
}
