/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(WESTROAD);

    set_long_desc("The West road is a road cut among the huge vallenwoods. " +
		  "It twists and turns between the giant trunks and " +
		  "beneath the thick green canopy of foliage above. " +
		  "The road continues northwest and southeast, to the " +
		  "northwest you spot a large vallenwood.");

    add_exit(TDIR + "west_road6", "northwest");
    add_exit(TDIR + "west_road4", "southeast");
}


