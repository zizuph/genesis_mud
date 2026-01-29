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
		  "to the southeast and north. The trees loom high above " +
		  "you. Their limbs form a canopy that protects you from " +
		  "the harsh outside world.");

    add_exit(TDIR + "small_road4", "north");
    add_exit(TDIR + "small_road2", "southeast");
}



