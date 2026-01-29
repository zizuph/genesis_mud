#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Small Square");
    set_long("You find yourself at the base of a huge cliff that towers "+
      "far above you to the north, and continues east and west into the "+
      "distance. This seems to be the northwestern corner of a small "+
      "square. The cobblestones underfoot are moist and covered with "+
      "greenish grime. To the southwest is a large wooden building.\n");
    add_item(({"base","huge cliff","cliff"}),"The sheer walls of the "+
      "cliffside look completely unclimbable.\n");
    add_item(({"sheer walls","walls","sheer wall","wall"}),"The cliff "+
      "face is nearly perpindicular to the ground, clearly an extremely "+
      "difficult if not impossible climb.\n");
    add_item(({"small square","square"}),"It continues to the east, "+
      "southeast and south.\n");
    add_item(({"cobblestone","cobblestone"}),"The pavement is a bit "+
      "weathered and seems to be covered by a thin film of water, along "+
      "with moss, lichen and other rootless plants.\n");
    add_item(({"greenish grime","grime","moss","lichen","rootless plants","rootless plant","plants","plant"}),
      "Growing in the abundant number of cracks in the cobbles of the "+
      "square are many green plants, sustained by the ever present "+
      "moisture.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A rather large structure built out of hardwood planks. It is most likely "+
      "some sort of warehouse, judging by its appearance.\n");
    add_exit(PORT + "s6", "west");
    add_exit(PORT + "s8", "east");
    add_exit(PORT + "s24", "southeast");
    add_exit(PORT + "s23", "south");
}

