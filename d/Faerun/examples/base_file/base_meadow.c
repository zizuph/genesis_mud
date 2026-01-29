/*
 * Base Room Example
 * -- Finwe, June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

// this is a base file for outdoor rooms in Faerun
inherit FAERUN_OUTDOOR_BASE;

// This inherits the drink code from Gondor.
// Thanks Varian for letting us use it!
inherit "/d/Gondor/common/lib/drink_water.c";

// this defines the routine to create the room
void
create_meadow()
{
}


void
create_faerun_room()
{
    setuid();
    seteuid(getuid());

    ::create_faerun_room();
//    add_prop(ROOM_S_MAP_FILE,"base_file_example_map.txt");

    extraline = "Description of the meadow goes here.";

// This is the default short description of the room
    set_short("A grassy meadow");

// This is what you use to make the room instead of create_faerun_room(),
// create_room(), etc.
    create_meadow();

// These are things that describe the meadow and appear in all rooms
    add_item(({"meadow"}),
        "It is large field of grass. It stretches as far as you can see. " +
        "A brook runs through the grass from the east to the west.\n");
    add_item(({"grass"}),
        "The grass is green and rich looking. It comes uo to ankles. A " +
        "path runs through the grass.\n");

// This turns on room tells
    set_room_tell_time(60);

// This always happens in all rooms.
    add_room_tell("The grass waves in the breeze.");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

void
init()
{
    ::init();
    init_drink();
}

/*
 * Function name : add_path
 * Description   : adds descr of the path in the forest
 */
void add_path()
{
    add_item(({"road", "down", "ground", "path"}),
        "The path is well trodden trail that wanders through the meadow.\n");
// This gives the player a dynamic view of the sky when they examine it
    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");
// These are additional meadow noises that are added when this routine is used
    add_room_tell("Some deer watch you from a distance.");
    add_room_tell("A rabbit hops through the grass.");
    add_room_tell("A butterfly darts from flower to flower.");

}

/*
 * Function name : add_brook
 * Description   : adds descr of the brook
 */
void add_brook()
{
    add_item(({"brook", "stream"}),
        "It is a shallow body of water running through the meadow. It " +
        "babbles as it flows over rocks from the east to the west. Tall " +
        "grasses and wild flowers grow around the brook's edge.\n");
    add_item(({"rocks"}),
        "They are all sizes and lay in the brook. Some are large and " +
        "poke out of the water causing the brook to babble. The rocks " +
        "are rounded and smooth from the water flowing over them. \n");
    add_item(({"pebbles"}),
        "They are small rocks and lay on the bottom the brook. They are " +
        "rounded and smooth from rubbing against each other.\n");
    add_item(({"tall grass"}),
        "The tall grass grows along the edge of the brook. It green " +
        "and sways in the breeze.\n");
    add_item(({"flowers", "wild flowers", "wildflowers"}),
        "The wild flowers are all sizes and shapes. They grow alongside " +
        "the brook along with the tall grasses, and provide pops of " +
        "color to the meadow.\n");
}

/*
 * Function name : add_pond
 * Description   : adds descr of a pond
 */
void add_pond()
{
    add_item(({"pond"}),
        "The pond is small and irregulary shaped. It is full of fresh " +
        "water with bugs skating across the surface. The pond looks deep, " +
        "and the water clear enough that you see large fish swimming " +
        "around in the pond. Reeds grow around the edge of the pond.\n");
    add_item(({"water"}),
        "It looks fresh and clean. Perhaps you can drink it.\n");
    add_item(({"fish"}),
        "The fish in the pond are large and swim lazily around. They are " +
        "brown with black spots.\n");
    add_item(({"bugs"}),
        "They are all sizes and shapes. Some fly above the pond and " +
        "others skate across the surface.\n");
    add_item(({"surface"}),
        "The surface of the water is still. Occasionally a fish comes " +
        "to the surface or a bug skates across it.\n");
    add_item(({"reeds", "reed"}),
        "They are tall grasses growing around the edge of the pond. " +
        "The reeds are thin and provide some shade to the water.\n");

// These tells are only used when this routine is inherited.
    add_room_tell("A fish leaps out of the pond and then splashes in the water.");
    add_room_tell("Bugs skate across the pond's surface.");
    add_room_tell("'rbbt ... rbbt'");
}
