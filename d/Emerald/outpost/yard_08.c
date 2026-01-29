#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("In the center of the camp.");
    set_em_long("You are standing on a dirt path under a watchtower in " +
       "the middle of the camp. The platform which forms the floor of the " +
       "tower stands above your head supported by large logs and rocks. " +
       "You can travel in any direction, up a ladder into the watchtower, " +
       "east or west into wooden buildings, or follow the dirt " +
       "paths towards other areas of the camp.\n");

    add_item( ({"path", "dirt path", "dirt paths", "paths" }),
        "This well trodden paths are made of packed earth. Many footprints " +
        "dot the ground leading in all directions.\n");

    add_item( ({"tower", "towers", "watchtowers", "watchtower"}),
        "Tall watchtowers rise up in all corners of the camp. You feel very " +
        "vulnerable out here in the open. The tower above you can be " +
        "reached by traveling up a ladder.\n");

    add_item( ({"wooden building", "building"}),
        "A Wooden building stands to your south. The windowless building " +
        "is constructed from large logs and like all the structures in " +
        "the camp, it is well maintained.\n");

    add_item( ({"platform", "wooden platform" }),
        "Above your head is a wooden platform which forms the floor for " +
        "the tower. The wood has been shaped and cut into boards which " +
        "fit tightly together. There is a square hole cut into the " +
        "middle of the platform with a ladder securely fastened to " +
        "the north side of the hole.\n");

    add_item( ({"logs", "stones" }),
        "Thick logs and small stones form the support structure for the " +
        "tower. Three logs in each corner brace and secure the platform.\n");

    add_item( ({"hole" }),
        "A small hole in the platform marks the entrance to the tower " +
        "above. A ladder is fastened to the north side of the hole and " +
        "secured deep into the earth.\n");

    add_item( ({"ladder", "wooden ladder", "rungs", "steps" }),
        "A small, wooden ladder is secured to the north side of the " +
        "hole. The base of the ladder has been driven deep into the " +
        "ground for added stability. Large, wide steps show the wear " +
        "of frequent use, but look well maintained and secure.\n");

    add_exit("watchtower.c","up");
    add_exit("warroom.c","west");
    add_exit("yard_05.c","north");
    add_exit("armoury.c","east");
    add_exit("yard_11.c","south");
    add_exit("yard_04.c","northwest");
    add_exit("yard_06.c","northeast");
    add_exit("yard_10.c","southwest");
    add_exit("yard_12.c","southeast");

} 
