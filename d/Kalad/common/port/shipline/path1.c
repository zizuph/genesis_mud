#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Path");
    set_long("This is a narrow and rocky path leading along the base of "+
      "a huge cliff, which towers above you in the north. The weatherbeaten "+
      "path continues to the east and west.\n");
    add_item(({"narrow rocky path","narrow path","rocky path","path","weatherbeaten path"}),
      "Strewn with rocks and slippery from the crashing waves of water, the "+
      "rocky pathway looks treacherous.\n");
    add_item(({"huge cliff","cliff"}),"A sheer rock face that rises hundreds "+
      "of feet above you, apparently just one edge of a gigantic plateau.\n");
    add_item(({"rocks","rock"}),"Sharp grey stones that have fallen from "+
      "the cliff or have been eroded by the breaking of the waves.\n");
    add_exit(PORT + "shipline/path2", "east");
    add_exit(PORT + "shipline/path", "west");
}

