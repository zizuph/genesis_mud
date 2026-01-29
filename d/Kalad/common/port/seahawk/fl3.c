#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("A small cabin in the ship");
    set_long("You are within a small cabin in the lower level of the "+
      "Seahawk. This room is almost devoid of furnishings, and nearly "+
      "everything is covered in a thin layer of dust. The only items "+
      "in the room are a small bed and desk.\n");
    add_item(({"thin layer of dust","thin layer","layer","dust"}),
      "The dust blankets almost everything in the room, causing you to "+
      "choke slightly as you move about the area.\n");
    add_item(({"small bed","bed"}),"An ordinary bed, devoid of sheets and "+
      "pillows. Its mattress is filled with numerous holes.\n");
    add_item(({"mattress"}),"Tiny, three-inch wide holes cover the "+
      "surface of the mattress.\n");
    add_item(({"desk"}),"A small, functional desk used by the former "+
      "occupant of this room for writing and other mundane tasks.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl2", "south");
}

