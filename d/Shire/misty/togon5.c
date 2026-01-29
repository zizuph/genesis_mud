#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("East of Anduin");
    set_long("You are on the east bank of the Anduin, which stretches little eastward here "+
      "because of the Undeeps. Mirkwood lies to the north and "+
      "beyond the Anduin to the south, the hills of the Emyn Muil are visible. "+
      "Between Emyn Muil to the south and Mirkwood, there stretches a wide "+
      "empty plain.\n");

    add_exit(MISTY_DIR + "togon4", "northwest");
    add_exit(COMMON_DIR + "gondorlink2", "south");
}
