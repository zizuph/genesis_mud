/*
   Diamond. Beach. NW#3.

   nwb3.c
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
    add_my_desc("The western point of the Diamond Isle lies to " +
	"the southwest, along with the west entrance to Diamond " +
	"City. The beach also continues to the northeast.\n");
    AI(({"entrance","west entrance"}),
	"The entrance to the Western Corridor is off the western " +
	"point to the southwest, though it is not " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "w3", "southwest", 0);
    AE(DIROOM + "nwb2", "northeast", 0);
}
