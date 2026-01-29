#include "../default.h"
inherit PORT_ROOM;

create_port_room()
{
    set_short("A dark dismal corridor in the prison");
    set_long("This is a dark, dismal corridor in the prison. This rear section "+
      "of the cell appears even darker and in worse condition than the "+
      "front.\n");
    add_item(({"dark dismal corridor","dark corridor","dismal corridor","corridor","cell"}),
      "This area of the prison is filled with refuse, filling the air "+
      "with its horrible smell.\n");
    add_item(({"refuse"}),"Undescribable filth lies across the ground.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba8", "north",0,0,4);
    add_exit(PORT + "seahawk/ba10", "south",0,0,4);
}

