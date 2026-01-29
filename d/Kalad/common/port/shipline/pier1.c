#include "../default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Pier");
    set_long("The rickety wooden planks of the pier seem to sway with every "+
      "gust of wind from the sea. The planks end just to your east, where "+
      "part of the pier appears to have fallen into the sea.\n"+
      "A rocky path extends to the north.\n");
    add_item(({"rocky path","path"}),"A rock-strewn path that winds its way "+
      "to the north.\n");
    add_item(({"rickety wooden flanks","rickety planks","wooden planks","planks","plank"}),
      "They are rotten and have little maggots burrowing through them.\n");
    add_item(({"maggots","maggot"}),"Nasty little bugs!\n");
    add_item(({"sea"}),"A great wide expanse stretching out of sight into "+
      "the southern horizon.\n");
    add_exit(PORT + "shipline/pier", "west");
    add_exit(PORT + "shipline/path", "north");
    reset_room();
}

reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(PORT + "shipline/merchant");
	ob1 -> move_living("xxx", TO);
    }
}
