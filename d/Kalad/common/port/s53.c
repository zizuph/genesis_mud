#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Dead End");
    set_long("You find yourself at the end of a narrow street. All about "+
      "you are large buildings, save for the west, where a narrow street heads "+
      "towards the center of the Port District. The cobblestones underfoot "+
      "are moist and covered with grime.\n");
    add_item(({"end","narrow street","street"}),"A small roadway paved "+
      "in slate-grey cobbles.\n");
    add_item(({"large buildings","buildings","building"}),"Giant, "+
      "warehouse-type structures that tower above you and cast a shadow "+
      "over this place. A sign hangs over the building in the east.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement clearly shows the "+
      "the effects of time and the weather, as the ground is cracked and worn.\n");
    add_item(({"grime"}),"A number of rootless plants, such as moss "+
      "and lichen have taken to growing on the cobblestoned street because "+
      "of the area's wet environment.\n");
    add_item(({"sign"}),"It has lots of readable words on it.\n");
    add_exit(PORT + "s52", "west");
    add_exit(PORT + "s54", "east");
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
    " ----------+--------------------+\n"+
    " __________| ~~~~~~~~~~~~~~~~~~ |\n"+
    "           |      Mardon's      |\n"+
    "           |      Tar Shop      |\n"+
    "           | ~~~~~~~~~~~~~~~~~~ |\n"+
    "           +____________________+\n";
}

