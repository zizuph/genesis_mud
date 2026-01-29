

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("Old bed chamber");
    set_long("This chamber is ornately decorated with many "+
        "tapestries, paintings and pictures on the walls, "+
        "and beautiful flowers and bushes planted around it. "+
        "There were many natural beds here made from wood, cloth, "+
        "and leaves but they appear to have been abandoned long "+
        "ago. There are three exits from this chamber, one west, "+
        "one south, and one east.\n");

    add_item(({"tapestry","tapestries"}),"There are several beautiful "+
        "tapestries hanging on the walls. They are made from the "+
        "finest cloths in the land. Each of the depicts a different "+
        "Elemental God or Goddess in a different location around "+
        "Calia. On one of the tapestries you notice the following "+
        "inscription:\n\nOnce a home, a refuge, a sanctuary - today "+
        "a memory of reverence and service. This humble, ancient "+
        "shrine was home to the Elemental Worshippers before the "+
        "new Temple was built.\n");
    add_item(({"painting","picture","pictures","paintings"}),"These "+
        "paintings and pictures have been "+
        "painted by the finest artists in all of Calia, on the best "+
        "canvas in all of the lands. They show various members of "+
        "the circle consulting with each other, carving things into "+
        "their Elemental Tools, and many other scenes.\n");
    add_item(({"flower","flowers","bush","bushes","plant","plants"}),
        "The flowers, bushes and plants seem to still be very well "+
        "tended to, and add a peaceful nature to this room. Small "+
        "traces of sunlight filter in from the room onto them.\n");
    add_item(({"bed","beds","natural bed","natural beds"}),"The "+
        "beds look like they used to be very comfortable.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);

    add_exit(ELEMENTALIST_TEMPLE+"oldpost","west",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldboard","east",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldmedroom","south",0,1);
}
