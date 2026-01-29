inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    set_short("Dead end in Leah");
    set_long("   This is the dead end of the alley. There is garbage and trash "+
             "that blocks your path going west. Perhaps this trash is waiting to be "+
             "picked up. To the north is a brightly painted town house. To the east "+
             "is the alley way you came in on. You can still hear the noises from the "+
             "city. You can also hear the wild life from the forest which surrounds the entire village.\n\n");

   add_item(({"house", "townhouse"}), "The house is small, kept fairly tidy and "+
            "is painted yellow.\n");
   add_item("alley", "The alley looks like the home of homeless elves in the area.\n");
   add_item("centre", "Looking back east you can see the centre of Leah.\n");
   add_item("rags", "There are piles of dirty rags all over the alley. They look "+
            "like they were clothes at one time in the past.\n");
   add_item("newspapers", "The old, yellowed newspapers are folded neatly. They make "+
            "you think they may have been used as blankets by the people who sleep here.\n");
   add_item("cans", "Tin cans litter the alley. They are burned black. Perhaps they were "+
            "used to cook food.\n");
   add_item(({"rubbish", "trash"}),"The trash is mainly household goods "+
             "all dropped outside for collection.\n");

    add_exit(VILLAGE_DIR + "alley2", "east");
    add_exit(VILLAGE_DIR + "cabin3", "north");
}
