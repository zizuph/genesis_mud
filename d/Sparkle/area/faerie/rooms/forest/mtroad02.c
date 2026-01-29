/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "";

void
create_forest_room()
{
    set_short("A deep valley in the mountains");
    set_long(short() + ". " + s_desc_sky_outside_sky() + 
        "Trees surround you in the valley. They are ancient looking and " +
        "cover the mountains that rise in the distance. A track wanders " +
        "through the valley, surrounded by bushes and wildflowers. " + 
        extra_line + "\n");

    set_add_valley();
    add_std_herbs("forest");
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();

    add_exit(FOREST_DIR + "mtroad01", "east");
    add_exit(FOREST_DIR + "mtroad03", "southwest"); 
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    set_searched(0);
}

