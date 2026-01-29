#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Gateway lane");
    set_long("You are just east of Caravan Gate, walking along Gateway "+
      "Lane, which travels west-east along the massive city walls of "+
      "Kabal. To the south, many crowded buildings can be seen. Animal "+
      "refuse litters the ground.\n");

    add_item( ({ "walls", "wall" }),
      "Looking upward, you see that the city walls, which are made of the "+
      "finest stone, rise to a height of thirty feet.\n");

    add_item( ({ "buildings", "building" }),
      "Most of the structures are built out of hardy Kaladian wood, cut "+
      "from the forests of northern Kabal. Most of these structures are "+
      "small homes for the guards and other workers of the Caravan "+
      "district.\n");

    add_item( ({ "refuse", "animal refuse" }),
      "These are the remains of animal dung left behind by the horses and "+
      "other animals common in this district.\n");

    add_exit(CVAN + "caravan_gate", "west");
    add_exit(CVAN + "gateway/s6", "east");
}
