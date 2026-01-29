/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"

inherit SOLOUTROOM2;

create_solace_room()
{
    set_place(WESTROAD);

    set_long_desc("The West road stretches west and east among the huge " +
		  "vallenwoods. The limbs of the trees intertwine above " +
		  "you, providing a protective canopy from the harsh " +
		  "outside world. High above you, you are able to spot " +
		  "a bridge walk that runs north and south.");

    add_exit(ROOM6, "north");
    add_exit(TDIR + "west_road1", "east");
    add_exit(TDIR + "west_road3", "west");
    add_exit(ROOM7, "northeast");
    add_exit(ROOM5, "northwest");
}


