#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Small Road");
    set_long("You are standing on a small cobblestoned road that links "+
      "the center of the Port District in the north with the city docks in "+
      "the south. The cobbles beneath are slightly slippery from the moist "+
      "grime that blankets it. Large buildings lie west and east aside "+
      "the road.\n");
    set_time_desc("A large number of people are gathered around the "+
      "building to the east.\n","A few heavily-cloaked figures pass in and "+
      "out of the building to the east.\n");
    add_item(({"small cobblestoned road","small road","cobblestoned road","road"}),
      "A narrow roadway that passes between two large buildings, heading "+
      "in a north-south direction.\n");
    add_item(({"cobbles","cobble"}),"Small, slightly worn down stones "+
      "that are the primary source of pavement for the district.\n");
    add_item(({"moist grime","grime"}),"Rootless plants, such as moss "+
      "and lichen that have been mixed in among the usual dirt associated "+
      "with a port area.\n");
    add_item(({"large buildings","buildings","building"}),"Big, "+
      "warehouse-type structures. The edifice to your east has a large sign "+
      "hanging before it.\n");
    add_item(({"large sign","sign"}),"It has many legible words that you "+
      "could probably read.\n");
    add_cmd_item("sign","read","@@sign");
    add_exit(PORT + "s51", "north");
    add_exit(PORT + "s62", "east");
    add_exit(PORT + "s74", "south");
}

sign()
{
    return "---+------------------+\n"+
    "___|Welcome Newcomers!|\n"+
    "   |--------To--------|\n"+
    "   |The Seagull Center|\n"+
    "   |~~~~~~~~~~~~~~~~~~|\n"+
    "   |-Open at all times|\n"+
    "   +------------------+\n";
}

