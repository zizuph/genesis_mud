#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You find yourself at the base of a huge cliff that towers "+
      "far above you to the north, and continues east and west into the "+
      "distance. You are travelling along a narrow street along the base of "+
      "the cliff. The cobblestones beneath you are moist and covered with "+
      "greenish grime. To the south and southwest is a large wooden building.\n");
    add_item(({"base","huge cliff","cliff"}),"The sheer rock walls of the "+
      "cliff look extremely hard, if not impossible to climb.\n");
    add_item(({"narrow street","street"}),"A small cobblestoned roadway at the "+
      "base of the cliff.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and cracked, "+
      "and seems to be covered in a thin film of moisture.\n");
    add_item(({"greenish grime","grime"}),"Rootless plants, such as moss "+
      "and lichen cover the pavement, apparently sustained by the constant "+
      "amount of water present.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A rather large structure made out of hardwood planks. It is most "+
      "likely some sort of warehouse.\n");
    add_exit(PORT + "s5", "west");
    add_exit(PORT + "s7", "east");
}

