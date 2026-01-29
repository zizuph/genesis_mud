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
        "Wildflowers and bushes grow along the track that wanders " +
        "through this deep valley. The mountains rise in the distance, " +
        "its peaks hidden by clouds in the sky. " + extra_line + "\n");

    set_add_valley();
    add_std_herbs("forest"); 
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();

    add_exit(FOREST_DIR + "mtroad04", "south");
    add_exit(FOREST_DIR + "mtroad02", "northeast");
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

