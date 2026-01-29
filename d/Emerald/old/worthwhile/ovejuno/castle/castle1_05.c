/* Castle_room05-The Meeting Room.
 * Coded by Marisol (09/04/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV;

void
create_castle_room()
{
    set_short("The Meeting room");
    set_em_long("A high-ceiling room with a long table with chairs "+
        "in the center of it. In this room, the elven lord has his "+
        "meeting with his advisors. The white walls are decorated "+
        "with expensives tapestries and paintings. There is a "+
        "tall dirty window in the wall, opposite to the door, that "+
        "doesn't let enough light into the room. Torches are the main "+
        "source of illumination for this room. Soft rugs cover the "+
        "floor. Some servants are cleaning the room.\n");

    add_item("table",
        "A long rectangular ebony table. It surface shines with "+
        "polish and it reflects the firelight from the torches on "+
        "the walls.\n");

    add_rugs();

    add_item(({"tall dirty window", "dirty window", "window"}),
        "The windows is dirty from the outside. From the inside, you "+
        "can see that it is gleaming clean. But the outside "+
        "grime, dead leaves and debris won't let the light come in.\n");

    add_item("chairs",
        "Black wooden chairs match the color of the ebony table. "+
        "They are simple in design and seem comfortable to sit on. "+
        "All the chairs are padded with a soft material covered with "+
        "a silk fabric.\n");

    add_exit("castle1_02", "west");
}                                                                         
