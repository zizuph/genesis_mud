/**  DARGAARD KEEP ROOM **/

#pragma strict_types
#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit GUILD_IN;

void
reset_dargaard_room()
{
}

void
create_dargaard_room()
{
    set_short("Barracks in Dargaard Keep");
    set_long("You are standing in the barracks underneath Dargaard Keep. "+
             "Twelve rotten wooden beds are placed along the walls, and "+
             "a small wooden chest is placed next to each bed. A torn "+
             "and stained carpet covers the cold stone floor. The path "+
             "to the north leads into a dark corridor.\n");

    add_exit(GUILD_ROOM + "room13","north",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

int
start(string str)
{
    if (str != "here") 
    {
        write("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a death knight!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("Ok. You will awaken here in the future.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
