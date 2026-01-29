/*
   Diamond. Beach. S#3.

   s3.c
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
    add_my_desc("This is the southern point of Diamond Isle. The " +
	"main entrance to Diamond City is to the north, a pier " +
	"lies to the south, and the beach runs to the northwest " +
	"and northeast.\n");
    AI(({"entrance","main entrance","north"}),
	"The entrance to the Southern Corridor is to the north, " +
	"and is the only entrance accessable for non-affiliated members.\n");
    AI(({"pier","south"}),
	"That is where a ship comes to transport people to and from " +
	"the Isle.\n");

    AE(DIROOM + "swb3", "northwest", 0);
    AE(DIROOM + "s2", "north", 0);
    AE(DIROOM + "seb3", "northeast", 0);
    AE(DIROOM + "spier", "south", 0);
}
