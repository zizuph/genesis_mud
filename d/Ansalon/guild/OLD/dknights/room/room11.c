
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
    set_long("You are located in a dark corridor underneath Dargaard "+
             "Keep. It is almost impossible to see which way you "+
             "may be able to exit this place, however you think you "+
             "notice some light coming from the east, north and west.\n");

    add_exit(GUILD_ROOM + "room10","west",0);
    add_exit(GUILD_ROOM + "laboratory","east",0);
    add_exit(GUILD_ROOM + "room12","north",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

