#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Bayside Street");
    set_long("You are travelling on a street aside the bay. The cobblestones beneath you "+
      "are moist and covered with some greenish grime. To the northwest, "+
      "west and southwest "+
      "is a large wooden building. The sparkling bay lies gloriously to your "+
      "east, its beauty only mirrored by the skies above.\n");
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
      "warehouse by the size of it.\n");
    add_item(({"sparkling bay","bay"}),"A brilliant azure color, the "+
      "bay mirrors the deep blue of the skies above.\n");
    add_item(({"skies","sky"}),"They are a stunning azure in color, the "+
      "mirror image of the bay beneath.\n");
    add_exit(PORT + "s42", "north");
    add_exit(PORT + "s65", "south");
}

