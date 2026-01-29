/*
   Diamond. Beach. NE#2.

   neb2.c
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
    add_my_desc("You are halfway between the northern and eastern " +
	"points of the Diamond Isle. The beach continues to the " +
	"northwest and southeast.\n");

    AE(DIROOM + "neb1", "northwest", 0);
    AE(DIROOM + "neb3", "southeast", 0);
}
