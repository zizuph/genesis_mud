#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;
void
create_outpost_outside_room()
{
    set_short("Outside the southeastern tower.");
    set_em_long("You are standing below a tower in the southeast corner " +
       "of the outpost. The wooden platform which forms the base of the " +
       "tower stands above your head supported by large logs and stones. " +
       "A rough wooden wall runs along the ground to your south and " +
       "east, forming the perimeter of the grounds. A ladder leads up " +
       "to a hole in the platform and a dirt path leads northwest towards " +
       "the heart of the camp.\n");

    add_item( ({"tower", "southeastern tower", "wooden tower" }),
        "You are directly below the floor of the tower. From this angle, it " +
        "is hard to see much other than the large logs which support the " +
        "building, one in each corner of the structure.\n");

    add_item( ({"platform", "wooden platform" }),
        "Above your head is a wooden platform which forms the floor for " +
        "the tower. The wood has been shaped and cut into boards which fit " +
        "tightly together. There is a square hole cut into the middle of " +
        "the platform with a ladder securely fastened to the west side of " +
        "the hole.\n");

    add_item( ({"wall", "wooden wall", "perimeter", "rough wooden wall" }),
        "Large oaken logs stand straight up into the air forming the " +
        "perimeter of the camp. The tops of the logs are sharpened to " +
        "a point making any attempted journey over the walls a very costly " +
        "one indeed.\n");

    add_item( ({"path", "dirt path" }),
        "This well trodden path is made of packed earth. Many footprints " +
        "dot the ground leading between the tower and most of the camp " +
        "to the northwest.\n");


    add_item( ({"logs", "stones" }),
        "Thick logs and small stones form the support structure for the " +
        "tower. Three logs in each corner brace and secure the platform.\n");
 
    add_item( ({"hole" }),
        "A small hole in the platform marks the entrance to the tower " + 
        "above. A ladder is fastened to the west side of the hole and " +
        "secured deep into the earth.\n");

    add_item( ({"ladder", "wooden ladder", "rungs", "steps" }),
        "A small, wooden ladder is secured to the west side of the hole. " +
        "The base of the ladder has been driven deep into the ground for " +
        "added stability. Large, wide steps show the wear of frequent " +
        "use, but look well maintained and secure.\n");

    add_exit("yard_12.c","northwest");
    add_exit("setower.c","up");
} 
