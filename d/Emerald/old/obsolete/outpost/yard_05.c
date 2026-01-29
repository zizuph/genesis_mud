#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("Northern section of the outpost.");
    set_em_long("You are standing on a dirt path in the middle of the " +
       "northern sections of the outpost. The center of the camp can be " +
       "reached by following the path towards the south where a large " +
       "wooden watchtower rises from the ground. You can follow the " +
       "dirt path north, south, east or west from here.\n");

    add_item( ({"path", "dirt path" }),
        "This well trodden path is made of packed earth. Many footprints " +
        "dot the ground leading in all directions.\n");

    add_item( ({"tower", "towers", "watchtowers", "watchtower"}),
        "A tall watchtower rises up in just south of you in the middle " +
        "of the camp. Looking around, you also notice similar " +
        "watchtowers in all corners of the camp. You feel very " +
        "vulnerable out here in the open.\n");

    add_exit("yard_02.c","north");
    add_exit("yard_08.c","south");
    add_exit("yard_06.c","east");
    add_exit("yard_04.c","west");

} 
