
 /* A village room coded by Jaacar */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("A shabby hut");
    set_long("You are standing in a very small hut made "+
        "from thatched sea grasses, straw, bits of wood, "+
        "and mud to hold it all together.  The floor is "+
        "the white sand you are now familiar with having "+
        "walked on it to get here, covered with small "+
        "straw mats.  A single man "+
        "sits in this hut on the mats.  There is one exit in the "+
        "west wall, leading back to the village road.\n");

   add_item((({"sea grasses", "grasses", "thatched sea grasses"})),
      "The grasses are sea grasses and dried pampas fronds. "+
      "They are woven together to make the walls and ceiling.\n");
    add_item(({"mat","mats","sand","floor"}),"There are "+
        "small straw mats covering the white sand of the "+
        "floor of this hut.  They appear to be for resting "+
        "or sleeping on.\n");
    add_item("man","This man appears not to be looking directly "+
        "at you, but at the same time is fully aware of your "+
        "presence and every move here.  He is wearing more "+
        "clothing than any of the other natives of this "+
        "village.  Perhaps he is someone of great importance "+
        "here.\n");
   
   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);

    add_exit(BEACH+"village6","west",0,0);
}
