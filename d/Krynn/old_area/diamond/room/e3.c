/*
   Diamond. Beach. E#3.

   e3.c
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
    add_my_desc("This is the eastern point of Diamond Isle. The " +
	"eastern entrance to Diamond City is to the west, a pier " +
	"lies to the east, and the beach runs to the northwest " +
	"and southwest.\n");
    AI(({"entrance","eastern entrance","west"}),
	"The entrance to the Eastern Corridor is to the west, " +
	"and is the only accessable for affiliated members.\n");
    AI(({"pier","east"}),
	"That is where a ship comes to transport people to and from " +
	"the Isle.\n");

    AE(DIROOM + "neb3", "northwest", 0);
    AE(DIROOM + "e2", "west", 0);
    AE(DIROOM + "seb1", "southwest", 0);
    AE(DIROOM + "epier", "east", 0);
}
