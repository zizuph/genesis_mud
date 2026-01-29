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
    set_place(MAINROAD);

    set_long_desc("The road twists and turns here, cutting through the " +
		  "dense vallenwood forest. High overhead, the limbs " +
		  "mesh to form a thick green canopy. The road continues " +
		  "both to the north and south, to the north you can see " +
		  "a high mighty vallenwood tree. Running above your " +
		  "head is a wooden bridge-walk.");

    add_exit(TDIR + "main_road2", "north");
    add_exit(TDIR + "main_road4", "south");
}


