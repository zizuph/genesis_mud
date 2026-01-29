#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("Dirt path outside kitchen.");
    set_em_long("You are standing on a dirt path in the western section " +
       "of the outpost. Buildings rise up to your east and west while the " +
       "path leads away to the northeast and southeast into other areas " +
       "of the camp. You notice large towers rising up in the distance " +
       "off to your east, northwest and southwest.\n");

    add_item( ({"path", "dirt path" }),
        "This well trodden path is made of packed earth. Many footprints " +
        "dot the ground leading between the large building to your " +
        "west and the building to your east. The path winds northeast " +
        "and southeast to other areas of the camp.\n");

    add_item( ({"tower", "towers", "watchtowers", "watchtower"}),
        "Tall watchtowers rise up in all corners of the camp. You feel very " +
        "vulnerable out here in the open.\n");

    add_item( ({"buildings", "building"}),
        "Wooden buildings stand to your east and your west. Both buildings " +
        "are constructed from large logs and are built without windows. " +
        "The structure to your west is quite large.\n");

    add_exit("warroom.c","east");
    add_exit("lmesshl.c","west");
    add_exit("yard_10.c","southeast");
    add_exit("yard_04.c","northeast");
} 
