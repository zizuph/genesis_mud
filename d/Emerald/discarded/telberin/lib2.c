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
    set_short("A side room of the library");
    set_long("   This room is located off the foyer of the " +
        "library. The shelves are full books of different sizes, " +
        "colors, and ages. The room is musty smelling from the " +
        "many tomes here. Many of them are ancient looking. The " +
        "room is lit by light that filters down from the ceiling " +
        "through potted plants. Elves sit nearby at tables that " +
        "are arranged around the room. Some overstuffed chairs " +
        "are spread around the room.\n\n");
 
    add_item(({"skylight", "skylights"}),
        "Large skylights fill the ceiling. Bright light fills " +
        "the room from these windows.\n");
    add_item("light",
        "Subdued light fills the room from the skylights, filling " +
        "the room with a friendly glow.\n");
    add_item("walls",
        "You peer through the bookcases and the tree branches, " +
        "looking for the walls. They are a pale green color, and " +
        "make the room seem like you are in the midst of a forest " +
        "glade.\n");
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
    add_item("tables",
        "Sturdy oak tables are scattered around the room. There " +
        "are ample spots for you to sit and work at the tables.\n");
    add_item(({"trees", "plants", "potted plants", "potted trees",
            "foilage"}),
        "These trees are enormous. Normally trees don't grow this " +
        "large indoors. The branches almost seem to be reaching up " +
        "to the sky. The light from the skylights above must be " +
        "perfect for their needs, and the gardeners must take " +
        "special care of them.\n");
    add_item("branches",
        "You look closely at the branches. They gracefully " +
        "spread out and add an air of peace and quiet to the room.\n");
    add_item(({"overstuffed chairs", "overstuffed chair"}),
        "The over stuffed chairs look comfortable and inviting. " +
        "A few are vacant. Small tables are situated next to each " +
        "table. Some of the small tables are full of books from " +
        "other elves.\n");
    add_item(({"small table", "small tables"}),
        "These small tables are circular and sit to the the side " +
        "of the overstuffed chairs. Some are littered with books.\n");
    add_item(({"chair", "chairs"}),
        "Sturdy oak chairs are situated at the tables. Some " +
        "overstuffed chairs are spread around the room.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit( THIS_DIR + "lib_entr", "north");
}
