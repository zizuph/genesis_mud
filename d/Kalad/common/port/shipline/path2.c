#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Path");
    set_long("This is a narrow and rocky path leading along the base of "+
      "a huge cliff, which towers above you in the north. The weatherbeaten "+
      "path travels through a massive stone arch in the east, while the "+
      "rest of it heads towards the west.\n");
    add_item(({"narrow rocky path","narrow path","rocky path","path","weatherbeaten path"}),
      "Strewn with rocks and slippery from the crashing waves of water, the "+
      "rocky pathway looks treacherous.\n");
    add_item(({"huge cliff","cliff"}),"A sheer rock face that rises hundreds "+
      "of feet above you, apparently just one edge of a gigantic plateau.\n");
    add_item(({"rocks","rock"}),"Sharp grey stones that have fallen from "+
      "the cliff or have been eroded by the breaking of the waves.\n");
    add_item(({"massive stone arch","massive arch","stone arch","arch"}),
      "A large rock formation here at the base of the cliff. Years of "+
      "constant erosion from wind and water have created a U-shaped arch of "+
      "rock that blocks your field of view in the east. However, the rocky "+
      "path travels through the arch, continuing east.\n");
    add_exit(PORT + "shipline/path3", "east");
    add_exit(PORT + "shipline/path1", "west");
}

