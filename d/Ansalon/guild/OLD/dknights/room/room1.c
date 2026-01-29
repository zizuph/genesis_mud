
/**  DARGAARD KEEP ROOM **/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/guild/dknights/local.h"
#include <stdproperties.h>

inherit GUILD_IN;

void
reset_dargaard_room()
{
}

void
create_dargaard_room()
{
    set_short("Intersection underneath Dargaard Keep");
    set_long("You are standing in a gloomy hallway underneath Dargaard "+
             "Keep. A few torches lite up this place removing some of "+
             "darkness. The cold and moist air covers the area like a "+
             "blanket of smoke. The black charred walls are covered "+
             "with small patches of moss and fungi, adding a strong "+
             "smell to the air. The hallway continues to the north, "+
             "south, east and west.\n");

    add_exit(DROOM + "room2","west",0);
    add_exit(DROOM + "room3","east",0);
    add_exit(DROOM + "room4","north",0);
    add_exit(GUILD_ROOM + "room5","south",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

