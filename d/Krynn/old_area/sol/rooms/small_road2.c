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
    set_place(SMALLROAD);

    set_long_desc("The road twists and turns among the trees and continues " +
		  "to the east and northwest. Looking up, you see a " +
		  "wooden bridge-walk high up in a vallenwood.");

    add_exit(TDIR + "small_road3", "northwest");
    add_exit(TDIR + "small_road1", "east");
}



