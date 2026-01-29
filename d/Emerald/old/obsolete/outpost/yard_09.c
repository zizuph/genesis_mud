#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("Dirt path outside barracks.");
    set_em_long("You are standing on a dirt path in the eastern section " +
       "of the outpost. Buildings rise up to your east and west while the " +
       "path leads away to the northwest and southwest into other areas " +
       "of the camp. You notice large towers rising up in the distance " +
       "off to your west, northeast and southeast.\n");

    add_item( ({"path", "dirt path" }),
        "This well trodden path is made of packed earth. Many footprints " +
        "dot the ground leading between the large building to your east " +
        "and the building to your west. The path winds northwest and " +
        "southwest to other areas of the camp.\n");

    add_item( ({"tower", "towers", "watchtowers", "watchtower"}),
        "Tall watchtowers rise up in all corners of the camp. You feel very " +
        "vulnerable out here in the open.\n");

    add_item( ({"buildings", "building"}),
        "Wooden buildings stand to your east and your west. Both buildings " +
        "are constructed from large logs and are built without windows. " +
        "The structure to your east is quite large.\n");

    add_exit("lbrcks.c","east");
    add_exit("armoury.c","west");
    add_exit("yard_12.c","southwest");
    add_exit("yard_06.c","northwest");
} 
