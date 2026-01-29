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
    set_place(PLATFORM);

    set_long_desc("This is a small platform. Also, someone has built " +
		  "stairs leading down from here winding their way " +
		  "down in circles around the massive trunk. The " +
		  "bridge-walks extends to the north and northwest.");
    
    add_exit(TDIR + "bridge_walk21", "north");
    add_exit(TDIR + "bridge_walk22", "northwest");
    add_exit(TDIR + "ns_path2", "down");
}
