#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("The far end of the Seahawk");
    set_long("This is the far end of the ship. The floor beneath you "+
      "creaks and groans protestingly under your weight. Along the deck "+
      "are numerous scratches indicative of battle.\n");
    add_item(({"floor","deck"}),"The ship's upper deck bears a number of "+
      "long, deep scratches on its surface.\n");
    add_item(({"scratches","scratch"}),"The markings look like the result "+
      "of a heavy ballistae shot striking the deck.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat4", "north");
    add_exit(PORT + "seahawk/boat6", "northeast");
    add_exit(PORT + "seahawk/boat7", "west");
}

