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
    set_place(PARK);

    set_long_desc("This is the eastern part of the Solace Park. Small " +
		  "gazebos and picnic tables and benches line the edges " +
		  "of the road. Looking up, you see the dense canopy of " +
		  "vallenwood branches. The road goes west to the western " +
		  "part of this park and northeast to the Main road.");

    add_exit(TDIR + "main_road2", "northeast");
    add_exit(TDIR + "park2", "west");
}


