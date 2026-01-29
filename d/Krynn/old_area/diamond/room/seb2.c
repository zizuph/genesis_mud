/*
   Diamond. Beach. SE#2.

   seb2.c
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
    add_my_desc("You are halfway between the southern and eastern " +
	"points of the Diamond Isle. The beach continues to the " +
	"northeast and southwest.\n");

    AE(DIROOM + "seb1", "northeast", 0);
    AE(DIROOM + "seb3", "southwest", 0);
}
