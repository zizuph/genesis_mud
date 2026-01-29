/*
   Diamond. Beach. SE#1.

   seb1.c
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
	"the northeast, along with the east entrance to Diamond " +
	"City. The beach also continues to the southwest.\n");
    AI(({"entrance","east entrance"}),
	"The entrance to the Eastern Corridor is off the eastern " +
	"point to the northeast, though it is not " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "seb2", "southwest", 0);
    AE(DIROOM + "e3", "northeast", 0);
}
