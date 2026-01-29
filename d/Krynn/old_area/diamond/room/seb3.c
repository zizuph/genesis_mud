/*
   Diamond. Beach. SE#3.

   seb3.c
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
	"the southwest, along with the main entrance to Diamond " +
	"City. The beach also continues to the northeast.\n");
    AI(({"entrance","main entrance"}),
	"The entrance to the Southern Corridor is off the southern " +
	"point to the southwest, and it also is the only entrance " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "s3", "southwest", 0);
    AE(DIROOM + "seb2", "northeast", 0);
}
