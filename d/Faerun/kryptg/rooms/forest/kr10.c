/*
 * Path in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/orcmaker/orcmaker.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_FOREST;

#define ORCMAKER_DIR    "/d/Faerun/orcmaker/"
#define MAX_NPCS        4

static object *npc = allocate(MAX_NPCS);

object strong_orc;

string extraline = "";
int alarmed;

void
create_forest()
{
    set_short("Near the western border of" + FOR_NAME);
    set_extraline(forest_descr5(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr14", "northwest");
    add_exit(FOR_DIR + "kr15", "northeast");
    add_exit(FOR_DIR + "kr06", "southeast");
    add_exit(FOR_DIR + "kr05", "southwest");
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
    setuid(); 
    seteuid(getuid());

//    int index, npc_count;
//
//    setuid(); 
//    seteuid(getuid());
//
//    npc_count = random(MAX_NPCS);
//
//    if(npc_count ==0)
//        npc_count = 4;
//
//
//        for(index = 0; index < npc_count; index++)
//        {
//            if (!objectp(npc[index]))
//            {
//                npc[index] = clone_object(ORCMAKER_DIR+"orcmaker2");
//                npc[index]->set_orc_type(TOUGH);
////                npc[index]->set_restrain_path(FOR_DIR);
////                npc[index]->set_random_move(3);
//                npc[index]->move(TO);
//            }
//         }      
//     tell_room(TO,"A group of orcs rush in.\n");

    create_orcs();
}
