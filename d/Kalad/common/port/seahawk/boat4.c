#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{

    set_short("Central area of the Seahawk");
    set_long("You are standing in the central section of the ship. Above "+
      "you are many seagulls, filling the air with their loud calls. The "+
      "wooden deck here is scuffed and worn down.\n");
    add_item(({"seagulls","seagull"}),"Majestic white sea birds which "+
      "fly noisily overhead.\n");
    add_item(({"wooden deck","deck"}),"The wooden planks of the ship's "+
      "upper deck show the effects of long years of exposure to the harsh "+
      "environment of the sea.\n");
    add_item(({"wooden planks","planks","plank"}),"Tiny rat-holes are "+
      "scattered here and there along the length of a few planks. Tiny "+
      "chittering sounds from the dark holes.\n");
    add_item(({"rat-holes","dark holes","holes","hole"}),"Small, two-inch "+
      "wide holes in the deck.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat3", "west");
    add_exit(PORT + "seahawk/boat2", "north");
    add_exit(PORT + "seahawk/boat5", "south");
}

