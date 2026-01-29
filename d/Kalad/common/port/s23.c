#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Small Square");
    set_long("You are at the southwestern end of a small square. The "+
      "cobblestones beneath you are moist and covered in greenish grime. "+
      "To the west and southwest is a large wooden building, while another similar "+
      "structure is in the southeast. Further north is a towering cliff.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and "+
      "a bit weathered, and is covered ina thin film of water. As a result "+
      "of this a number of plants have grown on it.\n");
    add_item(({"greenish grime","grime","plants","plant"}),"Moss, lichen "+
      "and other rootless plants are growing on the pavement.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A great building made of hardwood planks, it looks like some sort "+
      "of warehouse. A small sign hangs over the part of the building immediately to "+
      "your west.\n");
    add_item(({"small sign","sign"}),"It has lots of legible words on it.\n");
    add_item(({"structure"}),"A large building made of wooden planks, "+
      "probably some warehouse.\n");
    add_item(({"towering cliff","cliff"}),"An enormous rock face that rises "+
      "above the district, further north.\n");
    add_exit(PORT + "s22", "west");
    add_exit(PORT + "s7", "north");
    add_exit(PORT + "s8", "northeast");
    add_exit(PORT + "s24", "east");
    add_exit(PORT + "s36", "south");
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "                &&&&&&&&&&&&&&&&&&&&&&&&&&&\n"+
    "                && Gorumn the Net Weaver &&\n"+
    "                &&  Many fine nets sold  &&\n"+
    "                &&         here!         &&\n"+
    "                && The cheapest in town! &&\n"+
    "                &&&&&&&&&&&&&&&&&&&&&&&&&&&\n"+
    "\n";
}

