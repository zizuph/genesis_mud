/*
 * Game path from farm02 garden to farm01 orchard
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARM;
// to orchard and from orchard paths
string to_orch = "south",
       to_path = "pt03_09";
string fr_orch = "west", 
       fr_path = "pt03_07";

void
create_farm_room()
{
    set_short("A wild game path");
    set_extraline(path8_descr() + " The path runs through the " +
        "area heading " + to_orch + " and " + fr_orch + ".");

    reset_room();
    set_add_game_path();

    add_exit(PATHS_DIR + to_path, to_orch, 0,0,1);
    add_exit(PATHS_DIR + fr_path, fr_orch, 0,0,1);
}

void reset_room()
{
}
