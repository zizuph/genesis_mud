
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
    set_short("The ancient library");
    set_long("This is without a doubt the library of Dargaard Keep. "+
             "Ancient books fills the different bookcases and old "+
             "scrolls are lying in piles on the floor. A wooden table "+
             "and two chairs are located in the center of the room. "+
             "The only exit out of this room is to the south.\n");

    add_exit(GUILD_ROOM + "room8","south",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

