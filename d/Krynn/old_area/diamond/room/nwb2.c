/*
   Diamond. Beach. NW#2.

   nwb2.c
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
    add_my_desc("You are halfway between the northern and western " +
	"points of the Diamond Isle. The beach continues to the " +
	"northeast and southwest.\n");

    AE(DIROOM + "nwb1", "northeast", 0);
    AE(DIROOM + "nwb3", "southwest", 0);
}
