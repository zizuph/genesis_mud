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

    set_long_desc("The West road makes a slight turn here and heads " +
		  "east and northwest. There is a small path leading " +
		  "south into a clearing with a mighty vallenwood.");

    add_item(({"small path","path"}),"The path appears to be relatively " +
             "well-travelled. No vegetation covers it.\n");
    add_exit(TDIR + "west_road5", "northwest");
    add_exit(TDIR + "west_road3", "east");
    add_exit(TDIR + "clearing1", "south");
}


