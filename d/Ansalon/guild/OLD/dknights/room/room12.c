
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
    set_long("You are standing in a well lite room underneath Dargaard "+
             "Keep. Small drops of condensed wated falls from the "+
             "ceiling a few meters above you. The constant drops of "+
             "water has made a few small pools with ice cold water. The "+
             "hallway continues to the south, northeast and northwest.\n");

    add_exit(GUILD_ROOM + "room11","south",0);
    add_exit(GUILD_ROOM + "armoury","northeast",0);
    add_exit(GUILD_ROOM + "room8","northwest",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

