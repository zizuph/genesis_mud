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
    set_place(NSPATH);

    set_long_desc("The path is winding further south into the forest. " +
		  "To the northeast, you see the Solace square. High " +
		  "above you, you can see a wooden bridge-walk.");

    add_exit(TDIR + "square", "northeast");
    add_exit(TDIR + "ns_path2", "south");
}



