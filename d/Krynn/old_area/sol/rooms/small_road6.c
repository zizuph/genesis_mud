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
		  "to the southwest and east. Looking up, you see a " +
		  "wooden bridge-walk leading southwest high up in " +
		  "the vallenwoods. To the southwest you spot a road.");

    add_exit(TDIR + "small_road5", "east");
    add_exit(TDIR + "west_road6", "southwest");
}



