/*
 * A room in the library in Telberin
 * Coded by Finwe
 * February 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_room()
{
    set_short("Main room in the library");
    set_long("   This is the main room of the library. The " +
        "shelves are full of ancient books of different sizes, " +
        "colors, and bindings. The room is musty smelly from the " +
        "ageless books. You don't see any tables here since the " +
        "room is so full of bookshelves. Large skylights in the " +
        "ceiling fill the room with bright light.\n\n");
 
    add_item(({"skylight", "skylights"}),
        "Large skylights fill the ceiling. Bright light fills " +
        "the room from these windows.\n");
    add_item("light",
        "The bright light shines down from the skylights.\n");
    add_item("walls",
        "They are a pale green color, and make the room seem " +
        "like you are in the midst of a forest glade.\n");
    add_item(({"down", "ground", "floor", "floors"}),
        "The well worn hardwood floors have been meticulously " +
        "cared for and have a rich glow and shine.\n");
    add_item(({"up", "ceiling"}),
        "Gazing up, you are unable to tell if you are looking at the " +
        "sky or the handiwork of an extremely talented artist. The " +
        "perfect shade of blue leaves you wondering how it was " +
        "obtained.\n");
    add_item(({"bookshelves", "shelves"}),
        "The shelves are sturdy and filled with many books. " +
        "Still they look capable of holding even more volumes.\n");
    add_item(({"books", "volumes", "tomes"}),
        "There are many rare and ancient books found on these " +
        "shelves. Who knows how wise you would be if only you " +
        "could read a fraction of them. Many of these books are " +
        "very ancient. They could have come from the earlier lands " +
        "the elves once possessed. It is a shame you can't read " +
        "their ancient language. A feeling of hungering fills your " +
        "soul as you long to read them.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit( THIS_DIR + "lib_entr", "east");
}
