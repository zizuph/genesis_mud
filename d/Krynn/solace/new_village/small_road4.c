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
    set_place(SMALLROAD);

    set_long_desc("The road twists and turns among the trees and continues " +
		  "to the southwest and south. The trees loom high above " +
		  "you. Their limbs form a canopy that protects you from " +
		  "the harsh outside world. One of the trees has a wooden " +
		  "staircase leading up to a platform high up in the tree.");

    add_exit(TDIR + "small_road3", "south");
    add_exit(TDIR + "small_road5", "southwest");
    add_exit(TDIR + "platform5", "up");
}



