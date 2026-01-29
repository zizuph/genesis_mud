/*
   Diamond. Beach. SW#2.

   swb2.c
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
    add_my_desc("You are halfway between the southern and western " +
	"points of the Diamond Isle. The beach continues to the " +
	"northwest and southeast.\n");

    AE(DIROOM + "swb1", "northwest", 0);
    AE(DIROOM + "swb3", "southeast", 0);
}
