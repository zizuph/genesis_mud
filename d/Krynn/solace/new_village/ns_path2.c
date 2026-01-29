/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM2;

create_solace_room()
{
    set_place(NSPATH);

    set_long_desc("At the end of the path is a mighty vallenwood, with a " +
		  "staircase leading down from a platform. The path " +
		  "extends further to the north.");

    add_exit(TDIR + "ns_path1", "north");
    add_exit(TDIR + "platform6", "up");
}



