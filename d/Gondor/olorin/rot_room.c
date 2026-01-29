/*
 *	Example room to test vbfc of first arg in add_exit()
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"

#define N_ROOMS		4

public string query_my_exit(int i);

static string *Exit_Rooms = ({ "/d/Gondor/workroom",
			       "/d/Rhovanion/workroom",
			       "/d/Shire/workroom",
			       "/d/Rhovanion/hazelnut/workroom", });

public void
create_gondor()
{
    set_short("Hazelnut's rotating room");
    set_long("This is Hazelnut's rotating room.\n");

    add_exit(&query_my_exit(0), "north", 0, 0, 0);
    add_exit(&query_my_exit(1), "east",  0, 0, 0);
    add_exit(&query_my_exit(2), "south", 0, 0, 0);
    add_exit(&query_my_exit(3), "west",  0, 0, 0);
}

public string
query_my_exit(int dir)
{
    return Exit_Rooms[ (find_object(CLOCK)->query_minute()/10 + dir) %
		      N_ROOMS ];
}
