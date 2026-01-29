
/**  DARGAARD KEEP ROOM **/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit GUILD_IN;

void
reset_dargaard_room()
{
}

void
create_dargaard_room()
{
    set_short("Hallway in Dargaard Keep");
    set_long("You are located in a fairly round hallway underneath "+
             "Dargaard Keep. The former beautiful crystal walls have "+
             "been burned making them almost jet-black. Two torches "+
             "managed to lite up this room, allowing you to see the "+
             "fungi and mosses that covers the walls and floor. The "+
             "hallway extends to the north, west and south. To the "+
             "east a large room emerges from the darkness.\n");

    add_exit(GUILD_ROOM + "room10","southeast",0);
    add_exit(GUILD_ROOM + "dknight_train","east",0);
    add_exit(GUILD_ROOM + "room7","north",0);
    add_exit(GUILD_ROOM + "room13","west",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

