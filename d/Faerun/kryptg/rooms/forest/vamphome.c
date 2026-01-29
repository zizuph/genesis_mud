/*
 * Path in the Kryptgarden
 * -- Finwe, August 2007
 *
 * Home for the Vampire sire.
 *
 * Nerull 2021
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_FOREST;

#define MAX_NPCS        3

object vamp_sire;

string extraline = "To the north, a deep ravine cuts through the forest.";

void
create_forest()
{
    seteuid(getuid());
     
    set_short("Near the northern border of" + FOR_NAME);
    set_extraline(forest_descr3(extraline));
    
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

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
    if(!vamp_sire)
    {
        vamp_sire = clone_object(NPC_DIR + "vamp_sire");
        vamp_sire->set_restrain_path(FOR_DIR);
        vamp_sire->set_random_move(3);
        vamp_sire->move(this_object());
    }
}
