/*
   Diamond. Beach. SW#1.

   swb1.c
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
	"the northwest, along with the west entrance to Diamond " +
	"City. The beach also continues to the southeast.\n");
    AI(({"entrance","west entrance"}),
	"The entrance to the Western Corridor is off the western " +
	"point to the northwest, though it is not " +
	"accessable for non-affiliated members.\n");

    AE(DIROOM + "swb2", "southeast", 0);
    AE(DIROOM + "w3", "northwest", 0);
}
