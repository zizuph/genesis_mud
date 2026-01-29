/*
   Diamond. Beach. N#3.

   n3.c
   -----------
   Coded ........: May 1997
   By ...........: Kentari
   
   Latest update : May 1997
   By .......... : Kentari

*/

#include "../local.h"

inherit BEACH;

public void
create_beach()
{
    add_my_desc("This is the northern point of Diamond Isle. The " +
	"northern entrance to Diamond City is to the south, a pier " +
	"lies to the north, and the beach runs to the southwest " +
	"and southeast.\n");
    AI(({"entrance","northern entrance","south"}),
	"The entrance to the Northern Corridor is to the south, " +
	"and is the only accessable for affiliated members.\n");
    AI(({"pier","north"}),
	"That is where a ship comes to transport people to and from " +
	"the Isle.\n");

    AE(DIROOM + "npier", "north", 0);
    AE(DIROOM + "nwb1", "southwest", 0);
    AE(DIROOM + "n2", "south", 0);
    AE(DIROOM + "neb1", "southeast", 0);
}
