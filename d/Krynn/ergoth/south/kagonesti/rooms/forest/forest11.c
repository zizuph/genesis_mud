#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest10", "west");
    add_exit(FOREST + "forest12", "east");

    set_short("On a footbridge over a creek");
    set_special(" You are on a narrow footbridge crossing a creek.");
                    
    add_item(({"bridge", "footbridge"}), "Someone has cut a tree trunk "
        + "lengthwise and placed the halves side-by-side across the creek, "
        + "forming this sturdy footbridge.\n");
    add_item("creek", "The banks of the creek are steep and wide, but "
        + "the bridge you are on spans it easily.\n");
}
