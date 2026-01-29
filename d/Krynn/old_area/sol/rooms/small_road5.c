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
		  "to the west and northeast. Looking up, you see a small " +
		  "house in one of the vallenwoods. An almost hidden track " +
		  "leads north among the trees to a clearing.");

    add_exit(C_SPLAINS, "north");
    add_exit(TDIR + "small_road4", "northeast");
    add_exit(TDIR + "small_road6", "west");
}



