/*
 * Path in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_FOREST;

string extraline = "There is an ancient citadel south of here.";

void
create_forest()
{
    set_short("Deep in" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    set_add_citadel();
    
    add_exit(FOR_DIR + "kr37", "northwest");
    add_exit(FOR_DIR + "kr38", "northeast");
    add_exit(FOR_DIR + "kr27", "southeast");
//    add_exit(CIT_DIR + "cit_ent", "south", "@@block_room@@"); 
//    add_exit(CIT_DIR + "cit_ent", "south"); 
    add_exit(FOR_DIR + "kr26", "southwest");
    reset_faerun_room();
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet, the citadel is closed for the time being.\n");
    return 1;
} 
