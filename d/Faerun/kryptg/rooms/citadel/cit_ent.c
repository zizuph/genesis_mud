/*
 * Citadel in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CITADEL;

#define MAX_NPCS 3

static object *npc = allocate(MAX_NPCS);

string extraline = "";

void
create_citadel()
{
    INDOORS;
    NO_STEEDS;
    set_short("Entrance of a citadel");
    set_extraline("It is large and made of stone blocks. The room is " +
        "square shaped and deserted. The citadel is ancient looking " +
        "and probably made by dwarves. Even though it's very old looking " +
        "and run down, the citadel still looks formidable.");

    reset_faerun_room();
    set_add_citadel_out();
    
    add_exit(FOR_DIR + "kr32", "north");
    add_exit(CIT_DIR + "cit_1x", "south");
    add_exit(CIT_DIR + "cit_1b", "southwest");
    add_exit(CIT_DIR + "cit_1d", "southeast");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}
