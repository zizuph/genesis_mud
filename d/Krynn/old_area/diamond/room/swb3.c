/*
   Diamond. Beach. SW#3.

   swb3.c
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
    add_my_desc("The southern point of the Diamond Isle lies to " +
	"the southeast, along with the main entrance to Diamond " +
	"City. The beach also continues to the northwest.\n");
    AI(({"entrance","main entrance"}),
	"The entrance to the Southern Corridor is off the southern " +
	"point to the southeast, and it also is the only entrance " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "s3", "southeast", 0);
    AE(DIROOM + "swb2", "northwest", 0);
}
