#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#define NO_PEASANTS 3

object *peasants = allocate(NO_PEASANTS);

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("muddy");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("wheat");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("All around there are fields with different kinds of crops, "+
      "on this field there is growing "+crop+". To the northeast lies "+
      "a large farm.");

    add_item(({"house", "farm", "large farm", }), 
      "It looks like a rich well formed house.\n");

    add_exit(THORN_DIR + "f1","north",0,2);
    add_exit(THORN_DIR + "f4","west",0,2);

    reset_room();
}

void
add_npcs()
{
    int     ip = sizeof(peasants);

    while (ip--)
    {
	if (!objectp(peasants[ip]))
	{
	    peasants[ip] = clone_object(NPC_DIR + "peasants");
	    if (random(2))
	    {
		peasants[ip]->set_short(
		  implode(peasants[ip]->query_adjs(), " ") 
		  + " peasant walking across the fields");
		peasants[ip]->set_pshort("peasants walking across the fields");
		peasants[ip]->set_random_move(5);
		peasants[ip]->set_restrain_path(({FIELD_PATH}));
	    }
	    else
	    {
		peasants[ip]->set_short(
		  implode(peasants[ip]->query_adjs(), " ") 
		  + " peasant working on the field");
		peasants[ip]->set_pshort("peasants working on the field");
	    }
	    peasants[ip]->arm_me();
	    peasants[ip]->move_living("from the void", TO);
	}
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, add_npcs);
}

