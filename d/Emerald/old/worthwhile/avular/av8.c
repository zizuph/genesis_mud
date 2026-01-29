/*
 * AV8.c
 * On top of a bridge in Avular
 * - ALARON FEB 2000
 */

#include "defs.h"
#include <stdproperties.h>

inherit AVULAR_ROOM;

void
create_avular_room()
{
    set_short("A gray stone bridge");
    set_em_long("The dark, cobblestoned road becomes a long, flat stone "+
        "bridge here. The smooth, polished cobblestones give way to the "+
        "dark gray, unpolished stone blocks that make up this bridge. A "+
        "small stone fence rises up from the bridge on either side; high "+
        "enough for decoration, but too low to prevent anyone from "+
        "falling. The road disappears into the darkness just beyond the end "+
        "of the bridge to the north and south.\n");

    add_item( ({"bridge", "stone bridge", "gray stone bridge", "flat bridge",
             "flat stone bridge"}),
             "The bridge is long, and completely flat. It is too dark to see "+
             "what it is the bridge traverses below. It is made of huge, "+
             "perfectly square blocks of smoothly carved and sanded stone. A "+
             "small fence rises up from the bridge on the sides. It is too "+
             "low to prevent someone from falling, but just high enough "+
             "to appear decorative. Its height is perfectly uniform.\n");

    remove_item("down");
    add_item( ({"down", "under bridge", "beneath bridge"}),
            "You can't make out what is beneath the bridge through the "+
            "thick darkness.\n");

    add_item( ({"stones", "fence", "stone", "stone fence", "small fence"}),
            "The small, stone fence rises up from the bridge on both sides, "+
            "high enough to be decorative, but not high enough to actually "+
            "prevent anyone from falling. It is made of the same kinds "+
            "of perfectly shaped stones as the bridge, only smaller.\n");

    add_item( ({"road", "cobblestone road", "dark road",
               "dark cobblestone road", "stones", "cobblestones",
               "dark stone", "dark stones"}),
             "The road is formed of thousands of small, dark stones. Each "+
             "stone is individually carved and uniquely shaped, yet the "+
             "collection of all of the stones somehow meshes together to "+
             "form a narrow road.\n");

    add_item( ({"building", "buildings"}),
        "Several buildings peek out from behind the veil of suffocating "+
        "blackness surrounding this entire area. Each building is completely "+
        "unique, some of them shaped like domes, others traditionally "+
        "shaped like rectangles or squares.\n");

    add_exit(AVMAIN+"av7", "north");
    add_exit(AVMAIN+"av16", "south");
}
