/*
   Diamond. Beach. NE#1.

   neb1.c
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
    add_my_desc("The northern point of the Diamond Isle lies to " +
	"the northwest, along with the north entrance to Diamond " +
	"City. The beach also continues to the southeast.\n");
    AI(({"entrance","north entrance"}),
	"The entrance to the Northern Corridor is off the northern " +
	"point to the northwest, though it is not " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "n3", "northwest", 0);
    AE(DIROOM + "neb2", "southeast", 0);
}
