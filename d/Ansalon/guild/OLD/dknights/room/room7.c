
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
    set_long("You are located in one of the hallways underneath Dargaard "+
             "Keep. The familiar moss and fungi have been removed from "+
             "the walls here, revealing the black charred crystal that "+
             "walls was originaly constructed from. Two tapestries cover "+
             "the northeastern and southwestern wall. The hallway "+
             "continues to the south, east and northwest.\n");

    add_exit(GUILD_ROOM + "room6","northwest",0);
    add_exit(GUILD_ROOM + "room9","south",0);
    add_exit(GUILD_ROOM + "room8","east",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

