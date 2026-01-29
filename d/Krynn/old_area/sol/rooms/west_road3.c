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
		  "vallenwoods. High above you, you are able to spot " +
		  "a bridge walk that runs north and southwest.");

    add_exit(TDIR + "west_road4", "west");
    add_exit(TDIR + "west_road2", "east");
}


