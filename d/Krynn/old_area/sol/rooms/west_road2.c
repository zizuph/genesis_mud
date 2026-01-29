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
    set_place(WESTROAD);

    set_long_desc("The West road stretches west and east among the huge " +
		  "vallenwoods. The limbs of the trees intertwine above " +
		  "you, providing a protective canopy from the harsh " +
		  "outside world. High above you, you are able to spot " +
		  "a bridge walk that runs north and south.");

    add_exit(TDIR + "west_road3", "west");
    add_exit(TDIR + "west_road1", "east");
}


