/*
 * Library of Telberin
 * Coded Finwe
 * December 1996
 */
 
inherit "/std/room";
#include "/d/Emerald/defs.h"
#include "default.h"
 
 
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("Library entrance");
    set_long("   You are in the entrance of the library. You " +
        "pause a moment as a peaceful hush seems to settle into " +
        "your soul and you begin to relax. Elves in long flowing " +
        "robes move freely about here as they pass through here " +
        "and head elsewhere into the building. The room is lit " +
        "by sunlight filtering down through the large potted " +
        "plants. Some overstuffed chairs with small tables are " +
        "arranged around the room.\n\n");
 
    add_item(({"skylight", "skylights"}),
        "The large skylights which flood the room with light are " +
        "unbelievable and make it as bright indoors as it is " +
        "outside.\n");
    add_item("light",
        "Bright sunlight fills the room from the skylights, filling " +
        "the room with a friendly glow.\n");
    add_item("walls",
        "You peer through the tree branches and look for the " +
        "walls. They are a pale green color, and make the room seem " +
        "like you are in the midst of a forest glade.\n");
    add_item(({"down", "ground", "floor", "floors"}),
        "The well worn hardwood floors have been meticulously " +
        "cared for, and have a rich glow and shine.\n");
    add_item(({"up", "ceiling"}),
        "Gazing up, you are unable to tell if you are looking at the " +
        "sky or the handiwork of an extremely talented artist. The " +
        "perfect shade of blue leaves you wondering how it was " +
        "obtained.\n");
    add_item("tables",
        "Small circular oak tables are scattered around the room " +
        "with the overstuffed chairs. Some books are on some of " +
        "the tables.\n");
    add_item(({"trees", "plants", "potted plants", "potted trees",
            "foilage"}),
        "These trees are enormous. Normally trees don't grow this " +
        "large indoors. The branches almost seem to be reaching up " +
        "to the sky. The light from the skylights above must be " +
        "perfect for their needs, and the gardeners must take " +
        "special care of them.\n"); 
    add_item("branches",
        "You look closely at the branches. They spread out and " +
        "up towards the ceiling.\n");
 
    add_exit( AVENUE_DIR + "ave15", "out");
    add_exit( THIS_DIR + "lib2",  "south");
    add_exit( THIS_DIR + "lib1",  "west");
 
}
