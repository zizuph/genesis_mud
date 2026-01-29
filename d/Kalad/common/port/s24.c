#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Small Square");
    set_long("You are at the southeastern end of a small square. The "+
      "cobblestones underfoot are moist and covered in greenish grime. To "+
      "the east and south lies a large wooden building, and further north is a "+
      "towering cliff.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and "+
      "cracked, and seemingly covered in a thin film of moisture. As a result "+
      "a number of rootless plants have taken to growing on it.\n");
    add_item(({"rootless plants","rootless plant","plants","plant","greenish grime","grime"}),
      "Moss, lichen and a few other plants are growing in abundance on the "+
      "perpetually wet ground.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A structure made out of hardwood planks. From its great size, you ascertain "+
      "it to be some sort of warehouse. The section immediately to your "+
      "south has a sign hanging upon it.\n");
    add_item(({"sign"}),"A fancy-looking wooden sign. There is writing "+
      "on it.\n");
    add_item(({"towering cliff","cliff"}),"A massive sheer rock face, it "+
      "rises above you further north and runs west-east.\n");
    add_exit(PORT + "s23", "west");
    add_exit(PORT + "s7", "northwest");
    add_exit(PORT + "s8", "north");
    add_exit(PORT + "s37", "south");
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
    "---------------({})({})({})({}){(})({})({})({})---------------\n"+
    "               ({})    Exquisite Watches   ({})\n"+
    "               ({})           by           ({})\n"+
    "               ({})        Goldblum        ({})\n"+
    "               ({}) @@@@@@@@@@@@@@@@@@@@@@ ({})\n"+
    "               ({}) ~~~~~~~~~~~~~~~~~~~~~~ ({})\n"+
    "---------------({})({})({})({})({})({})({})({})---------------\n";
}

