/*
 *  Filename:    road_base.c
 *  Description: this file is to implement the warefare system to the
 *               road to Pax Tharkas. It will hold the area name definition
 *               and setup the name.
 *
 *  Coded by:    Boron Oct, 1999
 *
 *  Revision history:
 *
 */


#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit CONQUER_BASE
inherit PAXOUTROOM;


/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    reset_conquer_room();
    ::reset_krynn_room();
}

void
init()
{
    ::init();
    init_conquer();
}

