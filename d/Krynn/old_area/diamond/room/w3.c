/*
   Diamond. Beach. W#3.

   w3.c
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
    add_my_desc("This is the western point of Diamond Isle. The " +
	"western entrance to Diamond City is to the east, a pier " +
	"lies to the west, and the beach runs to the northeast " +
	"and southeast.\n");
    AI(({"entrance","western entrance","east"}),
	"The entrance to the Westhern Corridor is to the east, " +
	"and is the only accessable for affiliated members.\n");
    AI(({"pier","west"}),
	"That is where a ship comes to transport people to and from " +
	"the Isle.\n");

    AE(DIROOM + "wpier", "west", 0);
    AE(DIROOM + "nwb3", "northeast", 0);
    AE(DIROOM + "w2", "east", 0);
    AE(DIROOM + "swb1", "southeast", 0);
}
