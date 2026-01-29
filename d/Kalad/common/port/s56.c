#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Bayside Street");
    set_long("You are travelling on a street aside the bay. The cobblestones underfoot "+
      "are moist and covered with some greenish grime. To the east and northeast "+
      "is a large wooden building. The sparkling bay lies gloriously to your "+
      "west, its beauty only marred by the squat pier lying to the southwest.\n");
    add_item(({"street"}),"A narrow lane that seems to hug the side of "+
      "the bay, as one would a lover.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is weathered "+
      "and as a result has a rather extensive network of cracks on its "+
      "surface. Due to the constant moisture of the environment, a number "+
      "of plants have taken to growing on it.\n");
    add_item(({"greenish grime","grime","plants","plant"}),"Rootless "+
      "plants such as moss and lichen are growing on the pavement.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "An extremely large wooden structure, probably used as some sort of "+
      "warehouse by the size of it. The section of it immediately to your "+
      "east has a sign hung over it.\n");
    add_item(({"sign"}),"It has lots of legible words on it.\n");
    add_item(({"sparkling bay","bay"}),"A brilliant azure color, the "+
      "bay mirrors the deep blue of the skies above.\n");
    add_item(({"skies","sky"}),"They are a stunning azure in color, the "+
      "mirror image of the bay beneath.\n");
    add_item(({"squat pier","pier"}),"A small wooden appendage that sticks out "+
      "into the bay.\n");
    add_exit(PORT + "s46", "north");
    add_exit(PORT + "s57", "east");
    add_exit(PORT + "s69", "south");
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
    "                  {}{}{}{}{}{}{}{}{}{}{}{}\n"+
    "                  {}   Port  District   {}\n"+
    "                  {}  Shipping Offices  {}\n"+
    "                  {}    and Company     {}\n"+
    "                  {}{}{}{}{}{}{}{}{}{}{}{}\n"+
    "                  [][][][][][][][][][][][]\n";
}

