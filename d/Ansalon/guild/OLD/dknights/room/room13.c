
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
    set_long("You are located in a dark hallway in the lower levels of "+
             "Dargaard Keep. A few torches has been lit to attempt to "+
             "remove the gloom from this place. The black stone floor "+
             "and charred crystal walls are filled with different fungi "+
             "species. The path to the south leads to the barracks of "+
             "Dargaard Keep, while going east and north would take you "+
             "further into the dark hallways.\n");


    add_exit(GUILD_ROOM + "room14","north",0);
    add_exit(GUILD_ROOM + "room9","east",0);
    add_exit(GUILD_ROOM + "dknight_start","south",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    clone_object(GUILD_OBJ + "normal_board")->move(TO);

    reset_dargaard_room();
}

