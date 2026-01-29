#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Storage Room");
    set_long("A small room that is filled solely with many crates and "+
      "barrels, so many in fact that the stacks rise almost as high as "+
      "the ceiling. Everything is covered in a thin film of dust and "+
      "cobwebs.\n");
    add_item(({"crates","crate"}),"Large square wooden crates designed to "+
      "keep goods safe and dry on sea journeys. These crates look as if "+
      "they've been here for years, given the amount of dust and cobwebs "+
      "covering them.\n");
    add_item(({"barrels","barrel"}),"Large wooden barrels with iron "+
      "bands ringing them. They look to be the containers used "+
      "to store water for journeys.\n");
    add_item(({"stacks","stack"}),"The crates and barrels have all been "+
      "organized into seperate stacks, some rising as high as the ceiling.\n");
    add_item(({"ceiling"}),"Constructed from hardwood planks and supported "+
      "by thick wooden beams, they look every bit as sturdy as the day "+
      "the Seahawk first sailed.\n");
    add_item(({"hardwood planks","planks","plank"}),"A few holes are "+
      "barely visible but they don't seem to have had any effect on the "+
      "structural integrity of the deck.\n");
    add_item(({"thick wooden beams","thick beams","wooden beams","beams","beam"}),
      "As wide as one foot, the beams show remarkably little rotting "+
      "considering how old they are.\n");
    add_item(({"thin film of dust","thin film","film","dust"}),
      "It looks like greyish mist that blankets everything in the room.\n");
    add_item(({"cobwebs","cobweb"}),"The thin grey strands cover everything "+
      "in the room, mixing with the already present dust.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl6", "north");
}

