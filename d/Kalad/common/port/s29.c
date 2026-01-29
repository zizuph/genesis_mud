#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Bayside Street");
    set_long("You are travelling on a street aside the bay. Another "+
      "road intersects this bayside street from the west, where it heads "+
      "deeper into the district. Further north "+
      "you can see a huge cliff tower above the area. The cobblestones underfoot "+
      "are moist and covered with some greenish grime. To the southwest "+
      "is a large wooden building, while to the northwest is another "+
      "similar structure. The sparkling bay lies gloriously to your "+
      "east, its beauty marred only by the squat pier lying to the northeast.\n");
    add_item(({"bayside street","street"}),"A narrow lane that seems to hug the side of "+
      "the bay, as one would a lover.\n");
    add_item(({"road"}),"A narrow street that winds its way through "+
      "the buildings of the district, as would a snake through grass.\n");
    add_item(({"huge cliff","cliff"}),"A towering sheer rock face that "+
      "lies further north.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is weathered "+
      "and as a result has a rather extensive network of cracks on its "+
      "surface. Due to the constant moisture of the environment, a number "+
      "of plants have taken to growing on it.\n");
    add_item(({"greenish grime","grime","plants","plant"}),"Rootless "+
      "plants such as moss and lichen are growing on the pavement.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "An extremely large wooden structure, probably used as some sort of "+
      "warehouse by the size of it.\n");
    add_item(({"similar structure","structure"}),"It looks like a smaller version "+
      "of the large wooden building.\n");
    add_item(({"sparkling bay","bay"}),"A brilliant azure color, the "+
      "bay mirrors the deep blue of the skies above.\n");
    add_item(({"skies","sky"}),"They are a stunning azure in color, the "+
      "mirror image of the bay beneath.\n");
    add_item(({"squat pier","pier"}),"A small wooden appendage that sticks out "+
      "into the bay.\n");
    add_exit(PORT + "s13", "north");
    add_exit(PORT + "s28", "west");
    add_exit(PORT + "s42", "south");
}

