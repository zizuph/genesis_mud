#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest11", "east");
    add_exit(FOREST + "forest20", "southeast");
    
    set_creek_dir("east");
    set_special(" A bridge to the east allows you to cross the creek.");
    add_item(({"bridge", "footbridge"}), "Someone has cut a tree trunk "
        + "lengthwise and placed the halves side-by-side across the creek, "
        + "forming a sturdy footbridge.\n");
}
