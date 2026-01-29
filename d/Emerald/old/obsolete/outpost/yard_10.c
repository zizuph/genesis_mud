#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("Dirt path south of armoury.");
    set_em_long("You are standing on a dirt path in the southern section " +
       "of the outpost. A wooden building rises up to your north while " +
       "the path leads to towers in the southwestern and northeastern " +
       "directions. The path also leads towards other areas of the camp " +
       "to the northwest, the east and the southeast.\n");

    add_item( ({"path", "dirt path" }),
        "This well trodden path is made of packed earth. Many footprints " +
        "dot the ground leading in all directions.\n");

    add_item( ({"tower", "towers", "watchtowers", "watchtower"}),
        "Tall watchtowers rise up in all corners of the camp. You feel " +
        "very vulnerable out here in the open.\n");

    add_item( ({"wooden building", "building"}),
        "A Wooden building stands to your north. The windowless building " +
        "is constructed from large logs and like all the structures in " +
        "the camp, it is well maintained.\n");

    add_exit("yard_11.c","east");
    add_exit("yard_07.c","northwest");
    add_exit("yard_08.c","northeast");
    add_exit("yard_13.c","southwest");
    add_exit("yard_14.c","southeast");

} 
