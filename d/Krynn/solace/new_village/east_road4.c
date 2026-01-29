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
    set_place(EASTROAD);

    set_long_desc("The East road abruptly ends here. From the southeast " +
		  "you feel something like a cool wind. A big graveyard " +
		  "is there.");

    add_exit(C_GRAVES, "southeast");
    add_exit(TDIR + "east_road3", "northwest");
}


