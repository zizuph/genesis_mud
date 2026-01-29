/*
   Diamond. Beach. NE#3.

   neb3.c
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
    add_my_desc("The eastern point of the Diamond Isle lies to " +
	"the southeast, along with the east entrance to Diamond " +
	"City. The beach also continues to the northwest.\n");
    AI(({"entrance","east entrance"}),
	"The entrance to the Eastern Corridor is off the eastern " +
	"point to the southeast, though it is not " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "neb2", "northwest", 0);
    AE(DIROOM + "e3", "southeast", 0);
}
