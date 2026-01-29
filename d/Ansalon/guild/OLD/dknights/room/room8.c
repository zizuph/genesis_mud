
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
    set_long("You are standing deep within the burned Dargaard Keep. "+
             "The hallway here looks fairly infested with yellow "+
             "looking fungi. Two torches attached to the east wall "+
             "flickers making the shadows here dance slightly on the "+
             "ground. The path to the north leads into the library of "+
             "Dargaard Keep, while going to the southeast or west takes "+
             "you to another part the hallways.\n");

    add_exit(GUILD_ROOM + "room7","west",0);
    add_exit(GUILD_ROOM + "room12","southeast",0);
    add_exit(GUILD_ROOM + "library","north",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

