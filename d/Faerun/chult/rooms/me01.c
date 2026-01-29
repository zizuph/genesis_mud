/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CHULT_OUTDOOR;

string extraline = "";


string long_d(string str)
{
    return "test. "+ str;
}


void
create_chult_outdoor()
{
    set_short("Somewhere in Chult");
    
    set_extraline(long_d(extraline));

    //If we want herbs here.
    //add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me02", "east");
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
