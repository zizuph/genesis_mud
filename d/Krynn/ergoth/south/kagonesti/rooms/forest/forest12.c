#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest11", "west");
    add_exit(FOREST + "forest05", "northeast");
    add_exit(FOREST + "forest13", "east");
    add_exit(FOREST + "forest21", "southeast");


    set_creek_dir("west");
    set_special(" A bridge to the west allows you to cross the creek.");
    
    add_item(({"bridge", "footbridge"}), "Someone has cut a tree trunk "
        + "lengthwise and placed the halves side-by-side across the creek, "
        + "forming a sturdy footbridge.\n");
}
