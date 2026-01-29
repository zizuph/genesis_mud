/*
 * The master object for Solace
 *
 * by Rastlin
 */
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit SOLINROOM;

int gAttacked;

create_solace_room()
{
    set_short("The master room of Solace");
    set_long("This is the master room of Solace, it keep track on some " +
	     "quite useful stuff.\n");

    gAttacked = 0;  /* As a start, shouldn't be here */
}

/*
 * Function name: query_attacked
 * Returns:       True if Solace was attacked, false otherwise.
 */
public int
query_attacked()
{
    return gAttacked;
}
