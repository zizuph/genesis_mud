
/**  DARGAARD KEEP ROOM **/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit GUILD_IN;

object smith;

void
reset_dargaard_room()
{
    if(!objectp(smith))
    {
  	smith = clone_object(GUILD_NPC + "smith");
  	smith->move(TO);
    }
}

void
create_dargaard_room()
{
    set_short("Smith's Forge in Dargaard Keep");
    set_long("Loud noises of metal hitting metal can be heard within "+
             "this room. Thick steam emerges from a barrel next to "+
             "to a fiery forge in the western part of the room. A few "+
             "pieces of broken blackened solamnic armour are lying on "+
             "the floor. The path to the east take you out towards the "+
             "gloomy hallway.\n"+
             "A sign has been placed here.\n");

    add_exit(GUILD_ROOM + "room14","east",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

