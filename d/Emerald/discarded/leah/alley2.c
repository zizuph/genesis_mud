inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    set_short("Alley in the village of Leah");
    set_long("   You are standing in a small alley just west of the main street "+
             "in Leah. You can hear the hustle and bustle of the people on the "+
             "main street. This alley is clean and tidy.  You are standing "+
             "just outside a small house. You can smell the flowers from the "+
             "gardens all over the village. The alley contiues to the west.\n\n");

   add_item(({"people"}), "The people seem to be hurring around doing there daily shopping.\n");
   add_item(({"cobblestone", "cobblestones"}), "The cobblestones are laid in an intricate "+
           "pattern.\n");
   add_item(({"garden","north", "gardens"}), "The brilliance and colour of the garden spreads "+
            "out everywhere. The true beauty of the garden is too far away to truly appreciate.\n");
   add_item(({"house", "townhouse"}), "The house is old and built "+
               "of oak timbers. It is decorated in red paint and looks "+
               "like a house of hapiness and fun.\n");
   add_item(({"flowers"}), "The smell of roses, lilacs, and poppies are very "+
            "over whelming.\n");
   add_item(({"house", "townhouse"}), "The house is small, kept fairly tidy and "+
            "is painted yellow.\n");
   add_item("alley", "The alley looks like the home of homeless elves in the area.\n");
   add_item("centre", "Looking back east you can see the centre of Leah.\n");

    add_exit(VILLAGE_DIR + "alley3", "west");
    add_exit(VILLAGE_DIR + "road", "east");
    add_exit(VILLAGE_DIR + "cabin2", "north");
}
