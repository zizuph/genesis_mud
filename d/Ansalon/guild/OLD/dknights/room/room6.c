
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
    set_short("Hallway underneath Dargaard Keep");
    set_long("You are standing in the middle of an intersection. "+
             "Some torches lite up the east and west wall, allowing "+
             "you to see patches of moss and fungi covering the "+
             "charred walls. The blackened stone floor is completely "+
             "cleaned from debris and dirt. The hallways continue to "+
             "the north, southeast and southwest. The entrance to the "+
             "south leads to large room.\n");

    add_exit(GUILD_ROOM + "room5","north",0);
    add_exit(GUILD_ROOM + "throne","south",0);
    add_exit(GUILD_ROOM + "room7","southeast",0);
    add_exit(GUILD_ROOM + "room14","southwest",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

