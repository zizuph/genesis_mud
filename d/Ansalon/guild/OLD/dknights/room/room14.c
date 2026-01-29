
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
    set_short("Smith's Forge in Dargaard Keep");
    set_long("You are standing in a gloomy corridir in the lower levels "+
             "of Dargaard Keep. The air here is moist and cold, and even "+
             "a few torches are lit, they don't manage to remove must of "+
             "darkness here. The hallway continue to the northeast and "+
             "south. The path to the west takes you towards the Master "+
             "Smith of Dargaard Keep.\n");

    add_exit(GUILD_ROOM + "smith","west",0);
    add_exit(GUILD_ROOM + "room6","northeast",0);
    add_exit(GUILD_ROOM + "room13","south",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

