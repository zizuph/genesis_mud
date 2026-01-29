/*
 * A mountain track that connects the orc camp with the southern 
 * mountain road near Faerie.
 * By Finwe, January 2008
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "Animal prints cover this track which runs north into the mountains.";

void
create_forest_room()
{   
    setuid(); 
    seteuid(getuid());
    
    set_add_valley();
    add_std_herbs("forest");
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();
    reset_room();

    set_short("A dirty track in the mountains");
    set_long(mt_desc2(extra_line));

    add_item(({"prints", "animal prints"}),
        "They are impressions in the dirt left behind by many animals that pass this way. There are so many prints in the dirt that it's difficult to know how many have used this path.\n");
    add_item(({"dirt"}),
        "It is muddy and full of animal prints.\n");

    add_exit(FOREST_DIR + "path02", "north");
    add_exit(FOREST_DIR + "mtroad21", "southeast");
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

