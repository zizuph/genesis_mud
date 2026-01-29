/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gCoin;

reset_solace_room()
{
    if ((!gCoin) || (E(gCoin) != TO))
    {
        gCoin = clone_object("/d/Krynn/gnome/obj/fcoin");
	gCoin->move(TO);
    }
}

create_solace_room()
{
    set_place(MAINROAD);

    set_long_desc("The Solace main road is a road cut among the huge " +
		  "vallenwoods. It twists and turns between the giant " +
		  "trunks and beneath the thick green canopy of foliage " +
		  "above. You can leave the road here and venture west " +
		  "on a small road. The road leads north and south " +
		  "to other parts of Solace.");

    add_exit(TDIR + "main_road3", "north");
    add_exit(TDIR + "main_road5", "south");
    add_exit(TDIR + "small_road1", "west");

    reset_solace_room();
}


