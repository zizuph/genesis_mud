
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
    set_long("You are standing in a hallway under the burned Dargaard "+
             "Keep. Heavy rain from the levels above has caused water "+
             "to pour down from above, making fascinating stalactites "+
             "that fills the entire ceiling. The hallway continues to "+
             "the east and northwest.\n");

    add_exit(GUILD_ROOM + "room9","northwest",0);
    add_exit(GUILD_ROOM + "room11","east",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

